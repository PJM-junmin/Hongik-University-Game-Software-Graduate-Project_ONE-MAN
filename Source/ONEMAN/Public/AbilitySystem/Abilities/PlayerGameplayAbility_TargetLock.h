// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OMPlayerGameplayAbility.h"
#include "PlayerGameplayAbility_TargetLock.generated.h"

class UOMWidgetBase;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class ONEMAN_API UPlayerGameplayAbility_TargetLock : public UOMPlayerGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	// Tick Event
	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	// Target Switch
	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);
	
private:
	// Try LockOnTarget
	bool TryLockOnTarget();

	// Check the Target is Valid when LockOn
	void GetAvailableActorsToLock();

	// Get Nearest Target when Target is valid
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);

	// Find the Targets which is Around Player
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);

	// Draw a Widget
	void DrawTargetLockWidget();

	// Set Widget Position
	void SetTargetLockWidgetPosition();

	// Movement when LockOn
	void InitTargetLockMovement();

	// Use TargetLock Switch Key
	void InitTargetLockMappingContext();


	// Cancel TargetLock
	void CancelTargetLockAbility();

	// Dynamic Memory Clear
	void CleanUp();

	// Movement when LockOn Finished
	void ResetTargetLockMovement();

	// Finish TargetLock Switch Key
	void ResetTargetLockMappingContext();

	// LockOn Range
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float BoxTarceDistance = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	FVector TraceBoxSize = FVector(4000.0f, 4000.0f, 300.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TArray< TEnumAsByte < EObjectTypeQuery > > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowPersistentDebugShape = false;

	// Target LockOn Widget
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TSubclassOf<UOMWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockRotationInterpSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockMaxWalkSpeed = 150.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	UInputMappingContext* TargetLockMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockCameraOffsetDistance = 50.0f;

	// About Targets
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;

	UPROPERTY()
	UOMWidgetBase* DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	// MovementSpeed 
	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.0f;
};