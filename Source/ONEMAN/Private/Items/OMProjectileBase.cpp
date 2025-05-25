// Vince Petrelli all Rights Reserved


#include "Items/OMProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "OMFunctionLibrary.h"
#include "OMGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

// Debug
#include "OMDebugHelper.h"


AOMProjectileBase::AOMProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	projectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("projectileCollisionBox"));
	SetRootComponent(projectileCollisionBox);
	projectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	projectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	projectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	projectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	projectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	projectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	projectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("projectileNiagaraComponent"));
	projectileNiagaraComponent->SetupAttachment(GetRootComponent());

	projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectileMovementComp"));
	projectileMovementComp->InitialSpeed = 1200.0f;
	projectileMovementComp->MaxSpeed = 2000.0f;
	projectileMovementComp->Velocity = FVector(1.0f, 0.0f, 0.0f);
	projectileMovementComp->ProjectileGravityScale = 0.0f;

	// Actor's LifeTime
	InitialLifeSpan = 4.0f;
}

void AOMProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (projectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		projectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AOMProjectileBase::OnProjectileHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	/*if (otherActor)
	{
		Debug::Print(otherActor->GetActorNameOrLabel());
		Destroy();
	}*/

	BP_OnSpawnProjectileHitFX(hit.ImpactPoint);

	APawn* hitPawn = Cast<APawn>(otherActor);

	if (!hitPawn || !UOMFunctionLibrary::IsTargetPawnHostile(GetInstigator(),hitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UOMFunctionLibrary::NativeDoesActorHaveTag(hitPawn, OMGameplayTags::Player_Status_Blocking);
	
	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UOMFunctionLibrary::IsValidBlock(this, hitPawn);
	}

	FGameplayEventData data;
	data.Instigator = this;
	data.Target = hitPawn;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			hitPawn,
			OMGameplayTags::Player_Event_SuccessfulBlock,
			data
		);
	}
	else
	{
		// Apply projectile damage
		HandleApplyProjectileDamage(hitPawn, data);
	}
	
	Destroy();
}

void AOMProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (overlappedActors.Contains(otherActor))
		return;

	overlappedActors.AddUnique(otherActor);

	if (APawn* hitPawn = Cast<APawn>(otherActor))
	{
		FGameplayEventData data;
		data.Instigator = GetInstigator();
		data.Target = hitPawn;

		if (UOMFunctionLibrary::IsTargetPawnHostile(GetInstigator(), hitPawn))
		{
			HandleApplyProjectileDamage(hitPawn, data);
		}
	}
}


void AOMProjectileBase::HandleApplyProjectileDamage(APawn* inHitPawn, const FGameplayEventData& inPayload)
{
	checkf(projectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());

	const bool bWasApplied = UOMFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), inHitPawn, projectileDamageEffectSpecHandle);


	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			inHitPawn,
			OMGameplayTags::Shared_Event_HitReact,
			inPayload
		);
	}
}