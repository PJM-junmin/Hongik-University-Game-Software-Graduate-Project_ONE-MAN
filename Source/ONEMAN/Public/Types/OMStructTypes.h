// Vince Petrelli all Rights Reserved

#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "OMStructTypes.generated.h"

class UOMGameplayAbility;
class UONPlayerWeaponAnimInstance;
class UInputMappingContext;


// AbilitySet
USTRUCT(BlueprintType)
struct FOMPlayerAbilitySet
{
	GENERATED_BODY()

	// InputTag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	// Give Ability to Object
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UOMGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};


// PlayerWeaponData
USTRUCT(BlueprintType)
struct FOMPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UONPlayerWeaponAnimInstance> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FOMPlayerAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};


// Foot IK Kismet
USTRUCT(BlueprintType)
struct FOMIKTraceInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float fOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector ImpactLocation;
};