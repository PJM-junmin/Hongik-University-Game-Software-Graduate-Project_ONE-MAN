// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OMPickUpBase.generated.h"

class USphereComponent;

UCLASS()
class ONEMAN_API AOMPickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AOMPickUpBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick Up Interaction")
	USphereComponent* pickUpCollisionSphere;

	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

};
