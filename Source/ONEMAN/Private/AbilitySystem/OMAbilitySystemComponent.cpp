// Vince Petrelli all Rights Reserved


#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/OMPlayerGameplayAbility.h"
#include "OMGameplayTags.h"


void UOMAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
		return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
			continue;

		if (InInputTag.MatchesTag(OMGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}


void UOMAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(OMGameplayTags::InputTag_MustBeHeld))
		return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive()) 
			CancelAbilityHandle(AbilitySpec.Handle);
	}
}


// Give the Weapon's Ability To Others
void UOMAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FOMPlayerAbilitySet>& InDefaultWeaponAbilities, 
	const TArray<FOMPlayerSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, 
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
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

	for (const FOMPlayerSpecialAbilitySet& AbilitySet : InSpecialWeaponAbilities)
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


bool UOMAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());


	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

		if (!SpecToActivate->IsActive())
			return TryActivateAbility(SpecToActivate->Handle);
		
	}

	return false;
}
