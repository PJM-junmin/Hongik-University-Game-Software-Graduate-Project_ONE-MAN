// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/OMWeaponBase.h"
#include "Types/OMStructTypes.h"
#include "GameplayAbilitySpecHandle.h"

#include "OMPlayerWeapon.generated.h"



/**
 * 
 */
UCLASS()
class ONEMAN_API AOMPlayerWeapon : public AOMWeaponBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FOMPlayerWeaponData PlayerWeaponData;

	// Assign Weapon's Ability and Spec
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);


	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
