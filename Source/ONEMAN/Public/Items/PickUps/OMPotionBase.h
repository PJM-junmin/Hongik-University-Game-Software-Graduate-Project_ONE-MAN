// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/OMPickUpBase.h"
#include "OMPotionBase.generated.h"

class UOMAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class ONEMAN_API AOMPotionBase : public AOMPickUpBase
{
	GENERATED_BODY()
	
public:
	void Consume(UOMAbilitySystemComponent* abilitySystemComponent, int32 applyLevel);

protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult) override;


	UFUNCTION(BlueprintImplementableEvent, meta =(DisplayName = "On Potion Consumed"))
	void BP_OnPotionConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> potionGameplayEffectClass;

};
