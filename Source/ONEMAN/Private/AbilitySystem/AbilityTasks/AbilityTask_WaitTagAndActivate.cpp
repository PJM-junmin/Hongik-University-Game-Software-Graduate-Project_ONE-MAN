// Vince Petrelli all Rights Reserved


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitTagAndActivate.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"

UAbilityTask_WaitTagAndActivate* UAbilityTask_WaitTagAndActivate::WaitForTagAndTriggerInput(UGameplayAbility* OwningAbility, FGameplayTag ActiveTag, FGameplayTag InputTagToTrigger)
{
    UAbilityTask_WaitTagAndActivate* Task = NewAbilityTask<UAbilityTask_WaitTagAndActivate>(OwningAbility);
    Task->TargetTag = ActiveTag;
    Task->InputTagToTrigger = InputTagToTrigger;
    Task->SetWaitingOnAvatar();
    Task->ReadyForActivation();
    return Task;
}

void UAbilityTask_WaitTagAndActivate::Activate()
{
    Super::Activate();

    UOMAbilitySystemComponent* ASC = Cast<UOMAbilitySystemComponent>(AbilitySystemComponent);
    if (!ASC)
    {
        EndTask();
        return;
    }

    bTickingTask = true;
    bTriggered = false;
}

void UAbilityTask_WaitTagAndActivate::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    UOMAbilitySystemComponent* ASC = Cast<UOMAbilitySystemComponent>(AbilitySystemComponent);
    if (!ASC)
    {
        return;
    }


    if (ASC->HasMatchingGameplayTag(TargetTag))
    {
        if (bTriggered)
            return;
    
    }
}

