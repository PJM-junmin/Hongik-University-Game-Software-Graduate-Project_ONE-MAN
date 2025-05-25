// Vince Petrelli all Rights Reserved


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/OMEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UOMAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);


	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf < UOMEnemyGameplayAbility >& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
