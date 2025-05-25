// Vince Petrelli all Rights Reserved


#include "AbilitySystem/Abilities/OMEnemyGameplayAbility.h"
#include "Characters/OMCharacterEnemy.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "OMGameplayTags.h"


AOMCharacterEnemy* UOMEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedOMCharacterEnemy.IsValid())
	{
		CachedOMCharacterEnemy = Cast<AOMCharacterEnemy>(CurrentActorInfo->AvatarActor);
	}

	return CachedOMCharacterEnemy.IsValid() ? CachedOMCharacterEnemy.Get() : nullptr;
}

UEnemyCombatComponent* UOMEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UOMEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

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
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}
