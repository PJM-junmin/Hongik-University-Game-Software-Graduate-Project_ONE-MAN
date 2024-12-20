// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "OMCharacterBase.generated.h"

class UOMAbilitySystemComponent;
class UOMAttributeSet;
class UDataAsset_StartUpDataBase;

UCLASS()
class ONEMAN_API AOMCharacterBase : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOMCharacterBase();

	// GetAbilitySystemComponent <AbilitySystem Interface> 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Get PawnCombat Component by <PawnCombatInterface>
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	// Get PawnUI Component by <PawnUIInterface>
	virtual UPawnUIComponent* GetPawnUICompoenent() const override;

protected:

	// Connect the Controller to Character <APawn Interface>
	virtual void PossessedBy(AController* NewController) override;


	/********************************
			GameAblitySystem
	*********************************/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UOMAbilitySystemComponent* OMAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UOMAttributeSet* OMAttributeSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;


public:
	/*************************************
			Get GameAblitySystem
	**************************************/

	// ForceInline == 컴파일러가 함수를 호출하는 대신 함수 코드를 직접 호출 위치에 적는 기법
	FORCEINLINE UOMAbilitySystemComponent* GetOMAbilitySystemComponent() const { return OMAbilitySystemComponent; }
	FORCEINLINE UOMAttributeSet* GetOMAttributeSet() const { return OMAttributeSet; }

};
