// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ONBaseAnimInstance.h"
#include "ONCharacterAnimInstance.generated.h"

class AOMCharacterBase;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class ONEMAN_API UONCharacterAnimInstance : public UONBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	// Get the Character's References
	UPROPERTY()
	AOMCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	bool bHasAcceleration;
	
};
