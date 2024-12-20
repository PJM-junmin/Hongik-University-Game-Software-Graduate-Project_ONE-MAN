// Vince Petrelli all Rights Reserved


#include "AnimInstances/ONCharacterAnimInstance.h"
#include "Characters/OMCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// DebugHelper
#include "OMDebugHelper.h"

void UONCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AOMCharacterBase>(TryGetPawnOwner());
	if (OwningCharacter != nullptr)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
		// Debug::Print(TEXT("SuccessToGetCharacterMovement"));
	}
}

void UONCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	// GetCharacter's Velocity
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.0f;
}
