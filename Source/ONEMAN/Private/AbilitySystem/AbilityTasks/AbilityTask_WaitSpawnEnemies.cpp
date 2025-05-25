// Vince Petrelli all Rights Reserved


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"
#include "Characters/OMCharacterEnemy.h"


// DebugHelper
#include "OMDebugHelper.h"

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::waitSpawnEnemies(UGameplayAbility* owningAbility, FGameplayTag eventTag, TSoftClassPtr<AOMCharacterEnemy> softEnemyClassToSpawn, int32 numToSpawn, const FVector& spawnOrigin, float randomSpawnRadius)
{
	UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(owningAbility);
	Node->cachedEventTag = eventTag;
	Node->cachedSoftEnemyClassToSpawn = softEnemyClassToSpawn;
	Node->cachedNumToSpawn = numToSpawn;
	Node->cachedSpawnOrigin = spawnOrigin;
	Node->cachedRandomSpawnRadius = randomSpawnRadius;

	return Node;
}

void UAbilityTask_WaitSpawnEnemies::Activate()
{
	// Callback Func
	FGameplayEventMulticastDelegate& delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(cachedEventTag);

	delegateHandle = delegate.AddUObject(this, &ThisClass::OnGameplayEventReceived);

}

void UAbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(cachedEventTag);

	delegate.Remove(delegateHandle);

	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* inPayload)
{
	if (ensure(!cachedSoftEnemyClassToSpawn.IsNull()))
	{
		// Async Check the SoftObject Path
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			cachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)
		);
	}
	else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			didNotSpawn.Broadcast(TArray<AOMCharacterEnemy*>());
		}
		EndTask();
	}
}

//Spawn Enemy
void UAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
	UClass* loadedClass = cachedSoftEnemyClassToSpawn.Get();
	UWorld* world = GetWorld();

	if (!loadedClass || !world)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			didNotSpawn.Broadcast(TArray<AOMCharacterEnemy*>());
		}

		EndTask();
		return;
	}

	TArray<AOMCharacterEnemy*> spawnedEnemies;
	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for (int32 i = 0; i < cachedNumToSpawn; i++)
	{
		FVector randomLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, cachedSpawnOrigin, randomLocation, cachedRandomSpawnRadius);

		randomLocation += FVector(0.0f, 0.0f, 150.0f);

		const FRotator spawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

		AOMCharacterEnemy* spawnedEnemy = world->SpawnActor<AOMCharacterEnemy>(loadedClass, randomLocation, spawnFacingRotation, spawnParam);
		
		if (spawnedEnemy)
		{
			spawnedEnemies.Add(spawnedEnemy);
		}
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (!spawnedEnemies.IsEmpty())
		{
			onSpawnFinished.Broadcast(spawnedEnemies);
		}
		else
		{
			didNotSpawn.Broadcast(TArray<AOMCharacterEnemy*>());
		}
	}

	EndTask();
}
