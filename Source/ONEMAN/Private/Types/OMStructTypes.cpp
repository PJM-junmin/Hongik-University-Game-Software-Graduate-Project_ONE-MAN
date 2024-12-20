// Vince Petrelli all Rights Reserved

#include "Types/OMStructTypes.h"
#include "AbilitySystem/Abilities/OMGameplayAbility.h"

bool FOMPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant != nullptr;
}

