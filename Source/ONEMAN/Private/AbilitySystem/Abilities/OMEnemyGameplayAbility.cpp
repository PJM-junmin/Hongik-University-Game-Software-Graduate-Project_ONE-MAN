// Vince Petrelli all Rights Reserved


#include "AbilitySystem/Abilities/OMEnemyGameplayAbility.h"
#include "Characters/OMCharacterEnemy.h"
#include "Components/Combat/EnemyCombatComponent.h"


AOMCharacterEnemy* UOMEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedOMCharacterEnemy.IsValid())
	{
		CachedOMCharacterEnemy = Cast<AOMCharacterEnemy>(CurrentActorInfo->AvatarActor);
	}

	return CachedOMCharacterEnemy.IsValid() ? CachedOMCharacterEnemy.Get() : nullptr;
}

UEnemyCombatComponent* UOMEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
