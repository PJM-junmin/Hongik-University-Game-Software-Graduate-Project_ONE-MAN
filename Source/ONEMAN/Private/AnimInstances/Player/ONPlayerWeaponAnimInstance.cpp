// Vince Petrelli all Rights Reserved


#include "AnimInstances/Player/ONPlayerWeaponAnimInstance.h"
#include "AnimInstances/ONCharacterAnimInstance.h"

// Get Player AnimInstance
UONPlayerAnimInstance* UONPlayerWeaponAnimInstance::GetPlayerAnimInstance() const
{
	return Cast<UONPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
