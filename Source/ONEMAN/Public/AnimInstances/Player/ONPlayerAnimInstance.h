// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ONCharacterAnimInstance.h"
#include "ONPlayerAnimInstance.generated.h"

class AOMCharacterPlayer;

/**
 * 
 */
UCLASS()
class ONEMAN_API UONPlayerAnimInstance : public UONCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "References")
	AOMCharacterPlayer* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	bool bIsRest;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	float RestStateThreshold = 3.0f;

	float IdleElpasedTime;
};
