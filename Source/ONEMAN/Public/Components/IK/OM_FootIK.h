// Vince Petrelli all Rights Reserved
// https://darkcatgame.tistory.com/23
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OM_FootIK.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONEMAN_API UOM_FootIK : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOM_FootIK();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Foot_IK")
	float TraceDistance = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Foot_IK")
	FName LeftFootSocket = "foot_l";

	UPROPERTY(EditAnywhere, Category = "Foot_IK")
	FName RightFootSocket = "foot_r";

	UPROPERTY(EditAnywhere, Category = "Foot_IK")
	float IKInterpSpeed = 10.0f;

	// 초기 캡슐 반높이를 저장하는 변수
	float IKCapsuleHalfHeight = 96.0f;

	// foot's position and offset
	float LeftFootOffset = 0.0f;
	float RightFootOffset = 0.0f;
	FRotator LeftFootRotation = FRotator::ZeroRotator;
	FRotator RightFootRotation = FRotator::ZeroRotator;

	// Hip's position and offset
	float HipOffset = 0.0f;


public:
	// LineTrace
	UFUNCTION()
	FOMIKTraceInfo PerformIKTrace(float fTraceDistance, FName SocketName);

	UFUNCTION(BlueprintCallable, Category = "Foot_IK")
	float GetLeftFootOffset() const { return LeftFootOffset; }

	UFUNCTION(BlueprintCallable, Category = "Foot_IK")
	float GetRightFootOffset() const { return RightFootOffset; }

	UFUNCTION(BlueprintCallable, Category = "Foot_IK")
	FRotator GetLeftFootRotation() const { return LeftFootRotation; }

	UFUNCTION(BlueprintCallable, Category = "Foot_IK")
	FRotator GetRightFootRotation() const { return RightFootRotation; }

	UFUNCTION(BlueprintCallable, Category = "Foot_IK")
	float GetHipOffset() const { return HipOffset; }


public:
	// FootRotation
	UFUNCTION()
	FRotator NormalToRotator(FVector pVector);

	UFUNCTION()
	void IKUpdateFootRotation(float deltaTime, FRotator footRotatorValue, FRotator targetRotation, float interpSpeed);


public:
	// CapsuleCollider Position
	UFUNCTION()
	void IKUpdateCapsuleHalfHeight(float DeltaTime, float HipsShifts, bool bResetDefault);

	// IK Offset 보간 함수
	UFUNCTION()
	void IKUpdateFootOffset(float deltaTime, float targetValue, float& effectorValue, float interpSpeed);
};
