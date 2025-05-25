// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitTagAndActivate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTagTriggeredInputDelegate);

/**
 * 
 */
UCLASS()
class ONEMAN_API UAbilityTask_WaitTagAndActivate : public UAbilityTask
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintAssignable)
    FOnTagTriggeredInputDelegate OnTagTriggered;

    UFUNCTION(BlueprintCallable, Category = "AbilityTasks",
        meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
    static UAbilityTask_WaitTagAndActivate* WaitForTagAndTriggerInput(
        UGameplayAbility* OwningAbility,
        FGameplayTag ActiveTag,
        FGameplayTag InputTagToTrigger
    );

protected:
    virtual void Activate() override;

    virtual void TickTask(float DeltaTime) override;

private:
    FGameplayTag TargetTag;
    FGameplayTag InputTagToTrigger;
    bool bTriggered = false;  // Ability가 한 번 실행되었는지 체크
};
