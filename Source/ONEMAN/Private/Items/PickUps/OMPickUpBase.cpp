// Vince Petrelli all Rights Reserved


#include "Items/PickUps/OMPickUpBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AOMPickUpBase::AOMPickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	pickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("pickUpCollisionSphere"));
	SetRootComponent(pickUpCollisionSphere);
	pickUpCollisionSphere->InitSphereRadius(50.0f);
	pickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickUpCollisionSphereBeginOverlap);


}

void AOMPickUpBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, 
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{


}

