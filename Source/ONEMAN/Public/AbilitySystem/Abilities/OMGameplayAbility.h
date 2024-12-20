// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Types/OMEnumTypes.h"
#include "OMGameplayAbility.generated.h"

class UPawnCombatComponent;
class UOMAbilitySystemComponent;


// Single activation or Simultaneous activation(단일 활성화 or 동시 활성화)
UENUM(BlueprintType)
enum class EOMAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


protected:

	// GetAbilitySystemComponent <UGameplayAbility Interface> 
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	UPROPERTY(EditDefaultsOnly, Category = "OMAbility")
	EOMAbilityActivationPolicy AbilityActivationPolicy = EOMAbilityActivationPolicy::OnTriggered;

	// PureCastingComponent
	UFUNCTION(BlueprintPure, Category = "OneMan|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;


	UFUNCTION(BlueprintPure, Category = "OneMan|Ability")
	UOMAbilitySystemComponent* GetOMAbilitySystemComponentFromActorInfo() const;

	// Apply EffectSpecHandle
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "OneMan|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EOMSuccessType& OutSuccessType);


};
