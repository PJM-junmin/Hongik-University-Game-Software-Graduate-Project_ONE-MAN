// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OMPlayerGameplayAbility.h"
#include "PlayerGA_PickUpPotion.generated.h"

class AOMPotionBase;

/**
 * 
 */
UCLASS()
class ONEMAN_API UPlayerGA_PickUpPotion : public UOMPlayerGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// End

	UFUNCTION(BlueprintCallable)
	void CollectPotions();

	UFUNCTION(BlueprintCallable)
	void ConsumePotions();

private:
	UPROPERTY(EditDefaultsOnly)
	float boxTraceDistance = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	FVector traceBoxSize = FVector(100.0f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> stoneTraceChannel;

	UPROPERTY(EditdefaultsOnly)
	bool bDrawDebugShape = false;

	UPROPERTY()
	TArray<AOMPotionBase*> collectedPotions;

};
