// Vince Petrelli all Rights Reserved


#include "AbilitySystem/Abilities/OMPlayerGameplayAbility.h"

// PlayerCharacter
#include "Characters/OMCharacterPlayer.h"
#include "Controllers/OMCharacterPlayerController.h"

// AbilitySystemComponent
#include "AbilitySystem/OMAbilitySystemComponent.h"

// GameplayTags
#include "OMGameplayTags.h"

// Get the PalyerCharacter
AOMCharacterPlayer* UOMPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedOMCharacterPlayer.IsValid())
	{
		CachedOMCharacterPlayer = Cast<AOMCharacterPlayer>(CurrentActorInfo->AvatarActor);
	}

	return CachedOMCharacterPlayer.IsValid() ? CachedOMCharacterPlayer.Get() : nullptr;
}


// Get the PlayerController
AOMCharacterPlayerController* UOMPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedOMCharacterPlayerController.IsValid())
	{
		CachedOMCharacterPlayerController = Cast<AOMCharacterPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedOMCharacterPlayerController.IsValid() ? CachedOMCharacterPlayerController.Get() : nullptr;
}


// Get the Player's CombatComponent
UOMPlayerCombatComponent* UOMPlayerGameplayAbility::GetOMPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}


// Set PlayerDamageInfo
FGameplayEffectSpecHandle UOMPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass != nullptr);

	FGameplayEffectContextHandle ContextHandle = GetOMAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetOMAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		OMGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}
