// Vince Petrelli all Rights Reserved


#include "OMFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "OMGameplayTags.h"
#include "Types/OMCountDownAction.h"
#include "OMGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/OMSaveGame.h"

#include "OMDebugHelper.h" 

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
void UOMFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
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

bool UOMFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	// if Agent's Id is different each other, that means not a team
	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UOMFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UOMFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();
	
	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	// LeftHand Theory
	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);
	if (CrossResult.Z < 0.0f)
	{
		OutAngleDifference *= -1.0f;
	}

	if (OutAngleDifference >= -45.0f && OutAngleDifference <= 45.0f)
		return OMGameplayTags::Shared_Status_HitReact_Front;
	else if (OutAngleDifference < -45.0f && OutAngleDifference >= -135.0f)
		return OMGameplayTags::Shared_Status_HitReact_Left;
	else if (OutAngleDifference < -135.0f || OutAngleDifference > 135.0f)
		return OMGameplayTags::Shared_Status_HitReact_Back;
	else if (OutAngleDifference > 45.0f && OutAngleDifference <= 135.0f)
		return OMGameplayTags::Shared_Status_HitReact_Right;


	return OMGameplayTags::Shared_Status_HitReact_Front;
}



bool UOMFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	/*const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < -0.15f ? TEXT("Valid Block") : TEXT("InValidBlock"));
	Debug::Print(DebugString, DotResult < -0.15f ? FColor::Green : FColor::Red);*/

	return DotResult < -0.15f;

}

bool UOMFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* inInstigator, AActor* inTargetActor, const FGameplayEffectSpecHandle& inSpecHandle)
{
	UOMAbilitySystemComponent* sourceASC = NativeGetOMASCFromActor(inInstigator);
	UOMAbilitySystemComponent* targetASC = NativeGetOMASCFromActor(inTargetActor);

	FActiveGameplayEffectHandle activeGameplayEffectHandle = sourceASC->ApplyGameplayEffectSpecToTarget(*inSpecHandle.Data, targetASC);

	return activeGameplayEffectHandle.WasSuccessfullyApplied();
}

// CountDown
void UOMFunctionLibrary::CountDown(const UObject* worldContextObject, float totalTime, float updateInterval, 
	float& outRemainingTime, EOMCountDownActionInput countDownInput, 
	UPARAM(DisplayName = "Output")EOMCountDownActionOutput& countDownOutput, FLatentActionInfo latentInfo)
{
	UWorld* world = nullptr;

	if (GEngine)
		world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (!world)
		return;
	
	FLatentActionManager& latentActionManger = world->GetLatentActionManager();
	FOMCountDownAction* foundAction = latentActionManger.FindExistingAction<FOMCountDownAction>(latentInfo.CallbackTarget, latentInfo.UUID);
	
	if (countDownInput == EOMCountDownActionInput::Start) 
	{
		if (!foundAction)
		{
			// not memory lick in here
			latentActionManger.AddNewAction(
				latentInfo.CallbackTarget,
				latentInfo.UUID,
				new FOMCountDownAction(totalTime, updateInterval, outRemainingTime, countDownOutput, latentInfo)
			);
		}
	}

	if (countDownInput == EOMCountDownActionInput::Cancel)
	{
		if (foundAction)
		{
			foundAction->CancelAction();
		}
	}
}

// GameInstance
UOMGameInstance* UOMFunctionLibrary::GetOMGameInstance(const UObject* worldContextObject)
{
	if (GEngine)
	{
		if (UWorld* world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return world->GetGameInstance<UOMGameInstance>();
		}
	}

	return nullptr;
}


// GameInstance
void UOMFunctionLibrary::ToggleInputMode(const UObject* worldContextObject, EOMInputMode InInputMode)
{
	APlayerController* playerController = nullptr;

	if (GEngine)
	{
		if (UWorld* world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			playerController = world->GetFirstPlayerController();
		}
	}

	if (!playerController)
		return;

	FInputModeGameOnly gameOnlyMode;
	FInputModeUIOnly uiOnlyMode;

	switch (InInputMode)
	{
	case EOMInputMode::GameOnly:
		playerController->SetInputMode(gameOnlyMode);
		playerController->bShowMouseCursor = false;
		break;

	case EOMInputMode::UIOnly:
		playerController->SetInputMode(uiOnlyMode);
		playerController->bShowMouseCursor = true;
		break;

	default:
		break;
	}

}

// SaveGame
void UOMFunctionLibrary::SaveCurrentGameDifficulty(EOMGameDifficulty InDifficultyToSave)
{
	USaveGame* saveGameObject = UGameplayStatics::CreateSaveGameObject(UOMSaveGame::StaticClass());

	if (UOMSaveGame* omSaveGameObject = Cast<UOMSaveGame>(saveGameObject))
	{
		omSaveGameObject->savedCurrentGameDifficulty = InDifficultyToSave;

		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(omSaveGameObject, OMGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		// Debug::Print(bWasSaved ? TEXT("Difficulty Saved") : TEXT("Difficulty NOT Saved"));
	}

}

bool UOMFunctionLibrary::TryLoadSavedGameDifficulty(EOMGameDifficulty& outSavedDifficulty)
{
	if (UGameplayStatics::DoesSaveGameExist(OMGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0))
	{
		USaveGame* saveGameObject = UGameplayStatics::LoadGameFromSlot(OMGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		if (UOMSaveGame* omSaveGameObject = Cast<UOMSaveGame>(saveGameObject))
		{
			outSavedDifficulty = omSaveGameObject->savedCurrentGameDifficulty;

			// Debug::Print(TEXT("Loading Successful"), FColor::Green);
			return true;
		}
	}

	return false;
}


