// Vince Petrelli all Rights Reserved


#include "AbilitySystem/Abilities/PlayerGameplayAbility_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/OMCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/OMWidgetBase.h"
#include "Controllers/OMCharacterPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "OMFunctionLibrary.h"
#include "OMGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"

#include "OMDebugHelper.h"

void UPlayerGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (TryLockOnTarget())
	{
		InitTargetLockMovement();
		InitTargetLockMappingContext();
	}
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanUp();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPlayerGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor || 
		UOMFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, OMGameplayTags::Shared_Status_Death) ||
		UOMFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), OMGameplayTags::Shared_Status_Death))
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation =
		!UOMFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), OMGameplayTags::Player_Status_Rolling)
		&& 
		!UOMFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(),OMGameplayTags::Player_Status_Blocking);

	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetPlayerCharacterFromActorInfo()->GetActorLocation(),
			CurrentLockedActor->GetActorLocation()
		);

		LookAtRot -= FRotator(TargetLockCameraOffsetDistance, 0.0f, 0.0f);

		const FRotator CurrentControlRot = GetPlayerControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		GetPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.0f));
		GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.0f, TargetRot.Yaw, 0.0f));
	}
}

void UPlayerGameplayAbility_TargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	if (InSwitchDirectionTag == OMGameplayTags::Player_Event_SwitchTarget_Left) 
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

bool UPlayerGameplayAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return false;
	}

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
		return true;
	}
	else
	{
		CancelTargetLockAbility();
		return false;
	}
}

void UPlayerGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();

	TArray<FHitResult> BoxTraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * BoxTarceDistance,
		TraceBoxSize / 2.0f,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

AActor* UPlayerGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.0f;

	return UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UPlayerGameplayAbility_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
	
	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if (!AvailableActor || AvailableActor == CurrentLockedActor) continue;

		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormalized);

		if (CrossResult.Z > 0.0f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	}

}

void UPlayerGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forget to assign a valid widget class in Blueprint"));

		DrawnTargetLockWidget = CreateWidget<UOMWidgetBase>(GetPlayerControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget);
		DrawnTargetLockWidget->AddToViewport();
	}
}

void UPlayerGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;

	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetPlayerControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= (TargetLockWidgetSize / 2.0f);

	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UPlayerGameplayAbility_TargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;

	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;

}

void UPlayerGameplayAbility_TargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UPlayerGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UPlayerGameplayAbility_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurrentLockedActor = nullptr;

	if (DrawnTargetLockWidget != nullptr)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}

	DrawnTargetLockWidget = nullptr;

	TargetLockWidgetSize = FVector2D::ZeroVector;

	CachedDefaultMaxWalkSpeed = 0.0f;
}

void UPlayerGameplayAbility_TargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.0f)
	{
		GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void UPlayerGameplayAbility_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetPlayerControllerFromActorInfo())
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}