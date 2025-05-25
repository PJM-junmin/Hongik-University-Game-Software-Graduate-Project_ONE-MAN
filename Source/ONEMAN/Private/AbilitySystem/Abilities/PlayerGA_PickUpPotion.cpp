// Vince Petrelli all Rights Reserved


#include "AbilitySystem/Abilities/PlayerGA_PickUpPotion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/OMCharacterPlayer.h"
#include "Items/PickUps/OMPotionBase.h"
#include "Components/UI/OMPlayerUIComponent.h"


void UPlayerGA_PickUpPotion::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetPlayerUIComponentFromActorInfo()->OnPotionInteracted.Broadcast(true);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerGA_PickUpPotion::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetPlayerUIComponentFromActorInfo()->OnPotionInteracted.Broadcast(false);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


// if BeginOverlapped Potions
void UPlayerGA_PickUpPotion::CollectPotions()
{
	collectedPotions.Empty();

	TArray<FHitResult> traceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + -GetPlayerCharacterFromActorInfo()->GetActorUpVector() * boxTraceDistance,
		traceBoxSize / 2.0f,
		(-GetPlayerCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		stoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		traceHits,
		true
	);

	for (const FHitResult& traceHit : traceHits)
	{
		if (AOMPotionBase* foundPotion = Cast<AOMPotionBase>(traceHit.GetActor()))
		{
			collectedPotions.AddUnique(foundPotion);
		}
	}

	if (collectedPotions.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

// ConsumePotions
void UPlayerGA_PickUpPotion::ConsumePotions()
{
	if (collectedPotions.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AOMPotionBase* collectedPotion : collectedPotions)
	{
		if (collectedPotion)
		{
			collectedPotion->Consume(GetOMAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
	}
}
