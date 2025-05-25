// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameModes/OMGameModeBase.h"
#include "OMSurvivalGameMode.generated.h"

class AOMCharacterEnemy;

UENUM(BlueprintType)
enum class EOMSurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FOMEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AOMCharacterEnemy> softEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 minPerSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 maxPerSpawnCount = 3;

};

USTRUCT(BlueprintType)
struct FOMEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FOMEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 totalEnemyToSpawnThisWave = 1;
};


// delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChanged, EOMSurvivalGameModeState, CurrentState);

/**
 * 
 */
UCLASS()
class ONEMAN_API AOMSurvivalGameMode : public AOMGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void InitGame(const FString& mapName, const FString& options, FString& errorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

private:
	void SetCurrentSurvivalGameModeState(EOMSurvivalGameModeState InState);
	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();

	FOMEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;

	// SpawnTarget
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemies() const;

	// Destroy Delegate
	UFUNCTION()
	void OnEnemyDestroyed(AActor* destroyedActor);


	UPROPERTY()
	EOMSurvivalGameModeState currentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChanged OnSurvivalGameModeStateChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable* enemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 totalWavesToSpawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 currentWaveCount = 1;

	UPROPERTY()
	int32 currentSpawnedEnemiesCounter = 0;

	UPROPERTY()
	int32 totalSpawnedEnemiesThisWaveCounter = 0;


	UPROPERTY()
	TArray<AActor*> targetPointsArray;

	UPROPERTY()
	float timePassedSinceStart = -1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float spawnNewWaveWaitTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float spawnEnemiesDelayTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float waveCompletedWaitTime = 5.0f;

	UPROPERTY()
	TMap< TSoftClassPtr <AOMCharacterEnemy>, UClass* > preLoadedEnemyClassMap;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<AOMCharacterEnemy*>& InEnemiesToRegister);

	
};
