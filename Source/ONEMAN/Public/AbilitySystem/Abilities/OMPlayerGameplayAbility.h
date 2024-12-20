// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OMGameplayAbility.h"
#include "OMPlayerGameplayAbility.generated.h"

class AOMCharacterPlayer;
class AOMCharacterPlayerController;

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMPlayerGameplayAbility : public UOMGameplayAbility
{
	GENERATED_BODY()
	
public:
	// Get the PalyerCharacter
	UFUNCTION(BlueprintPure, Category = "ONEMAN|Ability")
	AOMCharacterPlayer* GetPlayerCharacterFromActorInfo();

	// Get the PlayerController
	UFUNCTION(BlueprintPure, Category = "ONEMAN|Ability")
	AOMCharacterPlayerController* GetPlayerControllerFromActorInfo();

	// Get the Player's CombatComponent
	UFUNCTION(BlueprintPure, Category = "ONEMAN|Ability")
	UOMPlayerCombatComponent* GetOMPlayerCombatComponentFromActorInfo();

	// Set PlayerDamageInfo
	UFUNCTION(BlueprintPure, Category = "ONEMAN|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

private:
	// use WeakedPtr
	TWeakObjectPtr<AOMCharacterPlayer> CachedOMCharacterPlayer;
	TWeakObjectPtr<AOMCharacterPlayerController> CachedOMCharacterPlayerController;

};
