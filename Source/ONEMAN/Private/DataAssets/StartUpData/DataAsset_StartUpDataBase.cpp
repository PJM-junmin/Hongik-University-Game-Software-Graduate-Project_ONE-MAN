// Vince Petrelli all Rights Reserved


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/OMGameplayAbility.h"

// Assign Abilities Function
void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UOMAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	// SetUp GameEffect in DataAsset
	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf < UGameplayEffect >& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) 
				continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UOMGameplayAbility>>& InAbilitiestoGive, UOMAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiestoGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UOMGameplayAbility>& Ability : InAbilitiestoGive) // Use Iterator
	{
		if (!Ability)
			continue;

		FGameplayAbilitySpec AbilitySpec(Ability); // Input the Ability's Info to MetaData
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); // Reference about to used
		AbilitySpec.Level = ApplyLevel; // Set the Level


		InASCToGive->GiveAbility(AbilitySpec);
	}

}
