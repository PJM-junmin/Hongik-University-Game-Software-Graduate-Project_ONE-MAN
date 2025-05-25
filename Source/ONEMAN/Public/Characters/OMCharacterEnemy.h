// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/OMCharacterBase.h"
#include "OMCharacterEnemy.generated.h"

class UEnemyCombatComponent;
class UOMEnemyUIComponent;
class UWidgetComponent;
class UBoxComponent;

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
	UEnemyCombatComponent* enemyCombatComponent;


	// CollisionBox
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* leftFootCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* rightFootCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName leftFootCollisionBoxAttachBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName rightFootCollisionBoxAttachBoneName;

#if WITH_EDITOR
	// ~Begin UObject Interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& propertyChangedEvent) override;
#endif

	// UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UOMEnemyUIComponent* enemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* enemyHealthWidgetComponent;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return enemyCombatComponent; }
	FORCEINLINE UBoxComponent* GetLeftFootCollisionBox() const { return leftFootCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightFootCollisionBox() const { return rightFootCollisionBox; }
};
