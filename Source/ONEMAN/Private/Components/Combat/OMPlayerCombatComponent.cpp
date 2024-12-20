// Vince Petrelli all Rights Reserved


#include "Components/Combat/OMPlayerCombatComponent.h"
#include "Items/Weapons/OMPlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "OMGameplayTags.h"

// DebugHelper
#include "OMDebugHelper.h"

AOMPlayerWeapon* UOMPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AOMPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AOMPlayerWeapon* UOMPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<AOMPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UOMPlayerCombatComponent::GetPlayerCurrentEquippWeaponDamageAtLevel(float InLevel) const
{
    return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}


void UOMPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    // Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" hit ") + HitActor->GetActorNameOrLabel(), FColor::Green);

    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        OMGameplayTags::Shared_Event_MeleeHit,
        Data
    );

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        OMGameplayTags::Player_Event_HitPause,
        FGameplayEventData()
    );
}

void UOMPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
    Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("'s weapon pulled from ") + InteractedActor->GetActorNameOrLabel(), FColor::Green);

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        OMGameplayTags::Player_Event_HitPause,
        FGameplayEventData()
    );
}
