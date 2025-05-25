// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class ONEMAN_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnHitTargetActor(AActor* HitActor) override;

protected:
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType toggleDamageType) override;
};
