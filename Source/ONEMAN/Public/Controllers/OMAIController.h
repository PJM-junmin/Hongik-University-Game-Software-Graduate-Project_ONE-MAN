// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "OMAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class ONEMAN_API AOMAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AOMAIController(const FObjectInitializer& ObjectInitalizer);

	// Begin IAbilitySystemInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	virtual void BeginPlay() override;

	// check the Something to interaction
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	// Check Radius of AI's Detector Range
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.0f;
};
