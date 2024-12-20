// Vince Petrelli all Rights Reserved


#include "AnimInstances/Player/ONPlayerAnimInstance.h"
#include "Characters/OMCharacterPlayer.h"

void UONPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter != nullptr)
	{
		OwningPlayerCharacter = Cast<AOMCharacterPlayer>(OwningCharacter);
	}

}

void UONPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);


	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.0f;
		bIsRest = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;
		bIsRest = IdleElpasedTime >= RestStateThreshold;
	}
}
