// Vince Petrelli all Rights Reserved


#include "OMFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"

UOMAbilitySystemComponent* UOMFunctionLibrary::NativeGetOMASCFromActor(AActor* InActor)
{
	check(InActor != nullptr);

	// If you get the Abilit;ySystemComponent by the Actor, you have to be one more check the Reference.
	return CastChecked<UOMAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}


// This Fuction add the Gameplay tag to Actor, So I used Static Fuction
void UOMFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UOMAbilitySystemComponent* ASC = NativeGetOMASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}

}


// This Fuction remove the Gameplay tag to Actor, So I used Static Fuction
void UOMFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UOMAbilitySystemComponent* ASC = NativeGetOMASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

// Check the Actor has Tag
bool UOMFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UOMAbilitySystemComponent* ASC = NativeGetOMASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}


// Create BP Node to Return
void UOMFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EOMConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EOMConfirmType::Yes : EOMConfirmType::No;
}

UPawnCombatComponent* UOMFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor != nullptr);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UOMFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EOMValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EOMValidType::Valid : EOMValidType::InValid;
	return CombatComponent;
}
