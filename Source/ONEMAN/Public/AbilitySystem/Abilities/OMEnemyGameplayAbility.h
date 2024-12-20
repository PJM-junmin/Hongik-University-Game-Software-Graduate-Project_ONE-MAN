// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OMGameplayAbility.h"
#include "OMEnemyGameplayAbility.generated.h"

class AOMCharacterEnemy;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMEnemyGameplayAbility : public UOMGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	AOMCharacterEnemy* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AOMCharacterEnemy> CachedOMCharacterEnemy;
};
