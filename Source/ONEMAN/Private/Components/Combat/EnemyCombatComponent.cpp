// Vince Petrelli all Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "OMGameplayTags.h"
#include "OMFunctionLibrary.h"
#include "Characters/OMCharacterEnemy.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/OMWeaponBase.h"

#include "OMDebugHelper.h"


void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	/*if (HitActor)
	{
		Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" is hitting ") + HitActor->GetActorNameOrLabel());
	}*/

	if (OverlappedActors.Contains(HitActor))
		return;

	OverlappedActors.AddUnique(HitActor);

	// check the HitTime, Implement block check
	bool bIsValidBloack = false;

	const bool bIsPlayerBlocking = UOMFunctionLibrary::NativeDoesActorHaveTag(HitActor, OMGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UOMFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), OMGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		// check if the block is valid
		bIsValidBloack = UOMFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBloack)
	{
		// Handle successful block
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			OMGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			OMGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType toggleDamageType)
{
	AOMCharacterEnemy* owningEnemyCharacter = GetOwningPawn<AOMCharacterEnemy>();
	check(owningEnemyCharacter);

	UBoxComponent* leftFootColligionBox = owningEnemyCharacter->GetLeftFootCollisionBox();
	UBoxComponent* rightFootColligionBox = owningEnemyCharacter->GetRightFootCollisionBox();

	check(leftFootColligionBox && rightFootColligionBox);

	switch (toggleDamageType)
	{
	case EToggleDamageType::LeftFoot:
		leftFootColligionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	case EToggleDamageType::RightFoot:
		rightFootColligionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
