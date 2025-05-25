// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemies.generated.h"

class AOMCharacterEnemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AOMCharacterEnemy*>&, SpawnedEnemies);

/**
 * 
 */
UCLASS()
class ONEMAN_API UAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "AbilityTasks", meta = (DisplayName = "Wait Gameplay Event and Spawn Enemies", 
		HidePin = "owningAbility", DefaultToSelf = "owningAbility", 
		BlueprintInternalUseOnly = "true", numToSpawn = "1", randomSpawnRadius = "200"))
	static UAbilityTask_WaitSpawnEnemies* waitSpawnEnemies(
		UGameplayAbility* owningAbility,
		FGameplayTag eventTag,
		TSoftClassPtr<AOMCharacterEnemy> softEnemyClassToSpawn,
		int32 numToSpawn,
		const FVector& spawnOrigin,
		float randomSpawnRadius
	);

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate onSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate didNotSpawn;

	// ~ Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	// ~ End UGameplayTask Interface

private:
	FGameplayTag cachedEventTag;
	TSoftClassPtr<AOMCharacterEnemy> cachedSoftEnemyClassToSpawn;
	int32 cachedNumToSpawn;
	FVector cachedSpawnOrigin;
	float cachedRandomSpawnRadius;
	FDelegateHandle delegateHandle;


	void OnGameplayEventReceived(const FGameplayEventData* inPayload);
	void OnEnemyClassLoaded();
};
