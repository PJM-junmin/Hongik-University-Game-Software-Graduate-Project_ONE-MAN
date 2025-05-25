// Vince Petrelli all Rights Reserved


#include "AnimInstances/ONBaseAnimInstance.h"
#include "OMFunctionLibrary.h"

UONBaseAnimInstance::UONBaseAnimInstance()
{
}

bool UONBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UOMFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
