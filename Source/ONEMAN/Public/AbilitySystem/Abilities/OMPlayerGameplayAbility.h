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

	// Get Player's UIComponent
	UFUNCTION(BlueprintPure, Category = "ONEMAN|Ability")
	UOMPlayerUIComponent* GetPlayerUIComponentFromActorInfo();

	// Set PlayerDamageInfo
	UFUNCTION(BlueprintPure, Category = "ONEMAN|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	// Get RemainingCoolDown
	UFUNCTION(BlueprintCallable, Category = "ONEMAN|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& totalCooldownTime, float& remainingCooldownTime);

private:
	// use WeakedPtr
	TWeakObjectPtr<AOMCharacterPlayer> CachedOMCharacterPlayer;
	TWeakObjectPtr<AOMCharacterPlayerController> CachedOMCharacterPlayerController;

};
