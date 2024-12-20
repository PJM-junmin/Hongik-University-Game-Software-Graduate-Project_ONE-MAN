// Vince Petrelli all Rights Reserved


#include "Components/IK/OM_FootIK.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Types/OMStructTypes.h"


// Sets default values for this component's properties
UOM_FootIK::UOM_FootIK()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOM_FootIK::BeginPlay()
{
	Super::BeginPlay();
}

void UOM_FootIK::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UOM_FootIK::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FOMIKTraceInfo traceLeft = PerformIKTrace(55.0f, "foot_l");
	FOMIKTraceInfo traceRight = PerformIKTrace(55.0f, "foot_r");

	
	IKUpdateFootRotation(DeltaTime, LeftFootRotation, NormalToRotator(traceLeft.ImpactLocation), 13.0f);
	IKUpdateFootRotation(DeltaTime, RightFootRotation, NormalToRotator(traceRight.ImpactLocation), 13.0f);


	float HipsOffset = UKismetMathLibrary::Min(traceLeft.fOffset, traceRight.fOffset);
	if (!(HipsOffset < 0.0f))
		HipsOffset = 0.0f;
	
	IKUpdateFootOffset(DeltaTime, HipsOffset, HipOffset, 13.0f);
	IKUpdateCapsuleHalfHeight(DeltaTime, HipsOffset, false);

	IKUpdateFootOffset(DeltaTime, traceLeft.fOffset - HipsOffset, LeftFootOffset, 13.0f);
	IKUpdateFootOffset(DeltaTime, -1.0f * (traceRight.fOffset - HipsOffset), RightFootOffset, 13.0f);
}


FOMIKTraceInfo UOM_FootIK::PerformIKTrace(float fTraceDistance, FName SocketName)
{
	FOMIKTraceInfo pOMIKTraceInfo;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	check(Character);

	// Set Linetraces startpoint and end point
	FVector pSocketLocation = Character->GetMesh()->GetSocketLocation(SocketName);
	FVector pLine_Start = FVector(pSocketLocation.X, pSocketLocation.Y, Character->GetActorLocation().Z);
	FVector pLine_End = FVector(pSocketLocation.X, pSocketLocation.Y,
		(Character->GetActorLocation().Z - IKCapsuleHalfHeight) - fTraceDistance);

	// Process Line Trace
	FHitResult pHitResult;
	TArray<AActor*> pIgnore;
	pIgnore.Add(GetOwner());

	bool bDebug = true;
	EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
	if (bDebug == true) eDebug = EDrawDebugTrace::ForOneFrame;

	bool bResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), pLine_Start, pLine_End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, pIgnore, eDebug, pHitResult, true);

	// Set ImpactNormal and Offset from HitResult
	pOMIKTraceInfo.ImpactLocation = pHitResult.ImpactNormal;
	if (pHitResult.IsValidBlockingHit() == true)
	{
		float fImpactLegth = (pHitResult.ImpactPoint - pHitResult.TraceEnd).Size();
		pOMIKTraceInfo.fOffset = 5.0f + (fImpactLegth - fTraceDistance);
	}
	else
		pOMIKTraceInfo.fOffset = 0.0f;
	

	return pOMIKTraceInfo;
}

FRotator UOM_FootIK::NormalToRotator(FVector pVector)
{
	float Pitch = UKismetMathLibrary::DegAtan2(pVector.Y, pVector.Z);
	float Roll = -1.0f * UKismetMathLibrary::DegAtan2(pVector.X, pVector.Z);
	return FRotator(Roll, 0.0f, Pitch);
}

void UOM_FootIK::IKUpdateFootRotation(float deltaTime, FRotator footRotatorValue, FRotator targetRotation, float interpSpeed)
{
	// Set Foot Rotation value with FInterpTo
	footRotatorValue = UKismetMathLibrary::RInterpTo(footRotatorValue, targetRotation, deltaTime, interpSpeed);
}

void UOM_FootIK::IKUpdateCapsuleHalfHeight(float DeltaTime, float HipsShifts, bool bResetDefault)
{
	// Character 캐스팅 확인
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("IK : Character is NULL"));
		return;
	}

	UCapsuleComponent* Capsule = Character->GetCapsuleComponent();
	if (!Capsule)
	{
		UE_LOG(LogTemp, Warning, TEXT("IK : Capsule is NULL"));
		return;
	}

	float TargetCapsuleHalfHeight = 0.0f; // 기본값: 원래 높이로 복귀

	// HipsShifts 값에 따른 캡슐 높이 조정
	if (bResetDefault)
		TargetCapsuleHalfHeight = IKCapsuleHalfHeight;
	else
	{
		// HipsShifts의 절대값을 반영하여 반높이 조정
		float AdjustedHeightOffset = UKismetMathLibrary::Abs(HipsShifts)*0.5f;
		TargetCapsuleHalfHeight = IKCapsuleHalfHeight - AdjustedHeightOffset;
	}

	// 캡슐 반높이를 보간하여 설정
	float CurrentCapsuleHalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
	float InterpolatedValue = UKismetMathLibrary::FInterpTo(CurrentCapsuleHalfHeight, TargetCapsuleHalfHeight, DeltaTime, 13.0f);

	Capsule->SetCapsuleHalfHeight(InterpolatedValue, true);
}

void UOM_FootIK::IKUpdateFootOffset(float deltaTime, float targetValue, float& effectorValue, float interpSpeed)
{
	effectorValue = FMath::FInterpTo(effectorValue, targetValue, deltaTime, interpSpeed);
}