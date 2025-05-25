// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteTaskOnTick.generated.h"

// declare Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DelaTime);

/**
 * 
 */
UCLASS()
class ONEMAN_API UAbilityTask_ExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()


public:
	UAbilityTask_ExecuteTaskOnTick();

	UFUNCTION(BlueprintCallable, Category = "AbilityTasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UAbilityTask_ExecuteTaskOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility);

	// Begin UGameplayTask Interface
	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;

};
