// Vince Petrelli all Rights Reserved


#include "Items/PickUps/OMPotionBase.h"
#include "Characters/OMCharacterPlayer.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "OMGameplayTags.h"


void AOMPotionBase::Consume(UOMAbilitySystemComponent* abilitySystemComponent, int32 applyLevel)
{
	check(potionGameplayEffectClass);

	UGameplayEffect* effectCDO = potionGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	abilitySystemComponent->ApplyGameplayEffectToSelf(
		effectCDO,
		applyLevel,
		abilitySystemComponent->MakeEffectContext()
	);

	BP_OnPotionConsumed();

}

void AOMPotionBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (AOMCharacterPlayer* overlappedCharacterPlayer = Cast<AOMCharacterPlayer>(otherActor))
	{
		overlappedCharacterPlayer->GetOMAbilitySystemComponent()->TryActivateAbilityByTag(OMGameplayTags::Player_Ability_PickUp_Potions);
	}
}
