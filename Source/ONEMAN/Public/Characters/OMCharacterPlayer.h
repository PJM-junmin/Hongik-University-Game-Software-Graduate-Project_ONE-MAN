// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/OMCharacterBase.h"
#include "GameplayTagContainer.h"
#include "OMCharacterPlayer.generated.h"

// forward decelation
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UOMPlayerCombatComponent;
class UOM_FootIK;
class UOMPlayerUIComponent;

/**
 * 
 */
UCLASS()
class ONEMAN_API AOMCharacterPlayer : public AOMCharacterBase
{
	GENERATED_BODY()
	
public:
	AOMCharacterPlayer();

	// Get PawnCombat Component by <PawnCombatInterface>
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	// Get PawnUI Component by <PawnUIInterface>
	virtual UPawnUIComponent* GetPawnUICompoenent() const override;
	virtual UOMPlayerUIComponent* GetPlayerUIComponent() const override;

protected:
	// GetAbilitySystemComponent <AbilitySystem Interface> 
	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	
private:
	/***********************
		   Components
	************************/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UOMPlayerCombatComponent* PlayerCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK", meta = (AllowPrivateAccess = "true"))
	UOM_FootIK* PlayerFootIKComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UOMPlayerUIComponent* OMPlayerUIComponent;

private:
	/***********************
		   Input Section
	************************/
	// CharacterData
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Look(const FInputActionValue& InputActionValue);
	void Move(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);


public:
	/***********************
		   Combat Section
	************************/
	FORCEINLINE UOMPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }

};
