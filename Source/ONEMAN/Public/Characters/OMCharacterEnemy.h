// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/OMCharacterBase.h"
#include "OMCharacterEnemy.generated.h"

class UEnemyCombatComponent;
class UOMEnemyUIComponent;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class ONEMAN_API AOMCharacterEnemy : public AOMCharacterBase
{
	GENERATED_BODY()
	

public:
	AOMCharacterEnemy();

	// Get PawnCombat Component by <PawnCombatInterface>
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	// Get PawnUI Component by <PawnUIInterface>
	virtual UPawnUIComponent* GetPawnUICompoenent() const override;
	virtual UOMEnemyUIComponent* GetEnemyUIComponent() const override;


protected:
	// Begin Play
	virtual void BeginPlay() override;

	// GetAbilitySystemComponent <AbilitySystem Interface> 
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UOMEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
