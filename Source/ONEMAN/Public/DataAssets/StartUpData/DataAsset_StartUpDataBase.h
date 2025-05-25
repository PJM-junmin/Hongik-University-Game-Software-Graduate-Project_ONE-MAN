// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UOMGameplayAbility;
class UOMAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class ONEMAN_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Apply Ability to Character or Object, and You can exert the Abilitys to control the extent of the effects.
	virtual void GiveToAbilitySystemComponent(UOMAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	// AutoActivate Abilities
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UOMGameplayAbility>> ActivateOnGivenAbilities;

	// When Event begin Activate Abilities
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UOMGameplayAbility>> ReactiveAbilities;

	// When StartUp GameplayEffect
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;


	// Set Priority about Abilities
	void GrantAbilities(const TArray<TSubclassOf<UOMGameplayAbility>>& InAbilitiestoGive, UOMAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

};
