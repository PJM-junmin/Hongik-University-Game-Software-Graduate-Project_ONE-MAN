// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "ONBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ONEMAN_API UONBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UONBaseAnimInstance();

protected:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;
};
