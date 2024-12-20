// Vince Petrelli all Rights Reserved


#include "AbilitySystem/Abilities/OMGameplayAbility.h"

// AbilitySystem
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Combat Component
#include "Components/Combat/PawnCombatComponent.h"


// Just do once Ability
void UOMGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EOMAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo != nullptr && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

// Finished Ability
void UOMGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EOMAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo != nullptr)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

// Get Avatar's ActorInfo and Findthe CombatComponent
UPawnCombatComponent* UOMGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

// Get Actor's AbilitySystemInfo
UOMAbilitySystemComponent* UOMGameplayAbility::GetOMAbilitySystemComponentFromActorInfo() const
{
	return Cast<UOMAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UOMGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(ASC && InSpecHandle.IsValid());

	return GetOMAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		ASC
	);
}


FActiveGameplayEffectHandle UOMGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EOMSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle =  NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EOMSuccessType::Successful : EOMSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}
