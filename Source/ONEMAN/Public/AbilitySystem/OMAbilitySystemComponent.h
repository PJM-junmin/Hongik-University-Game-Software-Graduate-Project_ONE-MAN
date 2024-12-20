// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Types/OMStructTypes.h"
#include "OMAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	

public:
	// Input AbilitySection
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);


	// Give the Weapon's Ability To Others
	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (ApplyLevel = "1"))
	void GrantPlayerWeaponAbilities(const TArray<FOMPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	// Remove Weapon's Ability by Others
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemovedGrantedPlayerWeaponHandleAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
};
