// Vince Petrelli all Rights Reserved


#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/OMGameplayAbility.h"


void UOMAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}
	
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
			continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}


void UOMAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}


// Give the Weapon's Ability To Others
void UOMAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FOMPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
		return;

	for (const FOMPlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
			continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}


// Remove Weapon's Ability by Others
void UOMAbilitySystemComponent::RemovedGrantedPlayerWeaponHandleAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
		return;

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
			ClearAbility(SpecHandle);
	}

	InSpecHandlesToRemove.Empty();
}
