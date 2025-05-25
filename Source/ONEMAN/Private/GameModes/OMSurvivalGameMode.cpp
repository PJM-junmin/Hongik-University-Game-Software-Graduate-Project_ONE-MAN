// Vince Petrelli all Rights Reserved


#include "GameModes/OMSurvivalGameMode.h"
#include "Engine/AssetManager.h"
#include "Characters/OMCharacterEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavigationSystem.h"
#include "OMFunctionLibrary.h"

// Debug Helper
#include "OMDebugHelper.h"

void AOMSurvivalGameMode::InitGame(const FString& mapName, const FString& options, FString& errorMessage)
{
	Super::InitGame(mapName, options, errorMessage);

	EOMGameDifficulty savedGameDifficulty;

	if (UOMFunctionLibrary::TryLoadSavedGameDifficulty(savedGameDifficulty))
	{
		currentGameDifficulty = savedGameDifficulty;
	}

}

void AOMSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();


	checkf(enemyWaveSpawnerDataTable, TEXT("Forgot to assign a balid data table in survival game mode blueprint"));

	SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState::WaitSpawnNewWave);

	totalWavesToSpawn = enemyWaveSpawnerDataTable->GetRowNames().Num();

	PreLoadNextWaveEnemies();
}


void AOMSurvivalGameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (currentSurvivalGameModeState == EOMSurvivalGameModeState::WaitSpawnNewWave)
	{
		timePassedSinceStart += deltaTime;

		if (timePassedSinceStart >= spawnNewWaveWaitTime)
		{
			timePassedSinceStart = -1.0f;
			SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState::SpawningNewWave);
		}
	}
	
	if (currentSurvivalGameModeState == EOMSurvivalGameModeState::SpawningNewWave)
	{
		timePassedSinceStart += deltaTime;

		if (timePassedSinceStart >= spawnEnemiesDelayTime)
		{
			// Handle spawn new enemies
			currentSpawnedEnemiesCounter += TrySpawnWaveEnemies();

			timePassedSinceStart = -1.0f;

			SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState::InProgress);
		}
	}

	if (currentSurvivalGameModeState == EOMSurvivalGameModeState::WaveCompleted)
	{
		timePassedSinceStart += deltaTime;

		if (timePassedSinceStart > waveCompletedWaitTime)
		{
			timePassedSinceStart = -1.0f;

			currentWaveCount++;

			if (HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState::WaitSpawnNewWave);
				PreLoadNextWaveEnemies();
			}
		}
	}

}


void AOMSurvivalGameMode::SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState InState)
{
	currentSurvivalGameModeState = InState;

	OnSurvivalGameModeStateChanged.Broadcast(currentSurvivalGameModeState);

}


bool AOMSurvivalGameMode::HasFinishedAllWaves() const
{
	return currentWaveCount > totalWavesToSpawn;
}


void AOMSurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves())
	{
		return;
	}

	preLoadedEnemyClassMap.Empty();


	for (const FOMEnemyWaveSpawnerInfo spawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (spawnerInfo.softEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			spawnerInfo.softEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[spawnerInfo, this]()
				{
					if (UClass* loadedEnemyClass = spawnerInfo.softEnemyClassToSpawn.Get())
					{
						preLoadedEnemyClassMap.Emplace(spawnerInfo.softEnemyClassToSpawn, loadedEnemyClass);
						
						/*Debug::Print(loadedEnemyClass->GetName() + TEXT(" is loaded"));*/
					}
				}
			)
		);
	}
}


FOMEnemyWaveSpawnerTableRow* AOMSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	// enemyWaveSpawnerDataTable->FindRow<FOMEnemyWaveSpawnerTableRow>()
	const FName rowName = FName(TEXT("Wave") + FString::FromInt(currentWaveCount));

	FOMEnemyWaveSpawnerTableRow* foundRow = enemyWaveSpawnerDataTable->FindRow<FOMEnemyWaveSpawnerTableRow>(rowName, FString());

	checkf(foundRow, TEXT("Could not find a valid row under the name %s in the data table"), *rowName.ToString());

	return foundRow;
}


int32 AOMSurvivalGameMode::TrySpawnWaveEnemies()
{
	if (targetPointsArray.IsEmpty()) 
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), targetPointsArray);
	}

	checkf(!targetPointsArray.IsEmpty(), TEXT("No valid target point found in level: %s for spawning enemies"), *GetWorld()->GetName());
	
	uint32 enemiesSpawnedthisTime = 0;

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	for (const FOMEnemyWaveSpawnerInfo& spawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (spawnerInfo.softEnemyClassToSpawn.IsNull()) 
			continue;

		const int32 numToSpawn = FMath::RandRange(spawnerInfo.minPerSpawnCount, spawnerInfo.maxPerSpawnCount);

		UClass* loadedEnemyClass = preLoadedEnemyClassMap.FindChecked(spawnerInfo.softEnemyClassToSpawn);

		for (int32 i = 0; i < numToSpawn; i++)
		{
			const int32 randomTargetPointIndex = FMath::RandRange(0, targetPointsArray.Num() - 1);
			const FVector spawnOrigin = targetPointsArray[randomTargetPointIndex]->GetActorLocation();
			const FRotator spawnRotation = targetPointsArray[randomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

			FVector randomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, spawnOrigin, randomLocation, 300.0f);
			
			randomLocation += FVector(0.0f, 0.0f, 150.0f);

			AOMCharacterEnemy* spawnedEnemy = GetWorld()->SpawnActor<AOMCharacterEnemy>(loadedEnemyClass, randomLocation, spawnRotation, spawnParam);

			if (spawnedEnemy)
			{
				spawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);

				enemiesSpawnedthisTime++;
				totalSpawnedEnemiesThisWaveCounter++;
			}

			if (!ShouldKeepSpawnEnemies())
			{
				return enemiesSpawnedthisTime;
			}
		}
	}
	
	return enemiesSpawnedthisTime;
}


bool AOMSurvivalGameMode::ShouldKeepSpawnEnemies() const
{
	return totalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->totalEnemyToSpawnThisWave;
}


void AOMSurvivalGameMode::OnEnemyDestroyed(AActor* destroyedActor)
{
	currentSpawnedEnemiesCounter--;

	// Debug::Print(FString::Printf(TEXT("CurrentSpawnedEnemiesCounter:%i, TotalSpawnedEnemiesThisWaveCounter:%i"), currentSpawnedEnemiesCounter, totalSpawnedEnemiesThisWaveCounter));

	if (ShouldKeepSpawnEnemies())
	{
		currentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}
	else if (currentSpawnedEnemiesCounter == 0)
	{
		totalSpawnedEnemiesThisWaveCounter = 0;
		currentSpawnedEnemiesCounter = 0;

		SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState::WaveCompleted);
	}
}

void AOMSurvivalGameMode::RegisterSpawnedEnemies(const TArray<AOMCharacterEnemy*>& InEnemiesToRegister)
{
	for (AOMCharacterEnemy* spawnedEnemy : InEnemiesToRegister)
	{
		if (spawnedEnemy)
		{
			currentSpawnedEnemiesCounter++;

			spawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
		}
	}

}
