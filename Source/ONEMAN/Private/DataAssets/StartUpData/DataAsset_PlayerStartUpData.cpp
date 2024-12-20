// Vince Petrelli all Rights Reserved


#include "DataAssets/StartUpData/DataAsset_PlayerStartUpData.h"

// GameplayAbility
#include "AbilitySystem/Abilities/OMPlayerGameplayAbility.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"


void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UOMAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);


	for (const FOMPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
			continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant); // Has Ability's Info
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); 
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
