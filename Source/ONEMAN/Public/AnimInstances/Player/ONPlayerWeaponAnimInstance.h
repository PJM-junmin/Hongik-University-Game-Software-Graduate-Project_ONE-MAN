// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ONBaseAnimInstance.h"
#include "ONPlayerWeaponAnimInstance.generated.h"

class UONPlayerAnimInstance;

/**
 * 
 */
UCLASS()
class ONEMAN_API UONPlayerWeaponAnimInstance : public UONBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (NotBlueprintThreadSafe))
	UONPlayerAnimInstance* GetPlayerAnimInstance() const;
};
