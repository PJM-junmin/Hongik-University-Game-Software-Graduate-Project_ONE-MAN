// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "GameplayTagContainer.h"
#include "OMPlayerUIComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityIconSlotUpdateDelegate, FGameplayTag, abilityInputTag, TSoftObjectPtr<UMaterialInterface>, softAbilityIconMaterial);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityCooldownBeginDelegate, FGameplayTag, abilityInputTag, float, totalCooldownTime, float, remainingCooldownTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPotionInteractedDelegate, bool, bShouldDisplayInputKey);

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAbilityIconSlotUpdateDelegate OnAbilityIconSlotUpdate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAbilityCooldownBeginDelegate OnAbilityCooldownBegin;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPotionInteractedDelegate OnPotionInteracted;
};
