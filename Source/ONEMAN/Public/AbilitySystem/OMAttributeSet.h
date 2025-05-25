// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "OMAttributeSet.generated.h"

class IPawnUIInterface;

// Attribute SingleTone Class
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UOMAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

	// Hp
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UOMAttributeSet, CurrentHealth)


	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UOMAttributeSet, MaxHealth)


	// To Use Skill. Like Mana
	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UOMAttributeSet, CurrentRage)


	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UOMAttributeSet, MaxRage)

	
	// Damage
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UOMAttributeSet, AttackPower)


	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UOMAttributeSet, DefensePower)


	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UOMAttributeSet, DamageTaken)


private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};
