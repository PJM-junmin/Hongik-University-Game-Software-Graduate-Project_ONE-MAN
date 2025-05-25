// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "OMProjectileBase.generated.h"

class UBoxComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;

struct FGameplayEventData;


UENUM(BlueprintType)
enum class EProjectileDamagePolicy : uint8
{
	OnHit, 
	OnBeginOverlap
};

UCLASS()
class ONEMAN_API AOMProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AOMProjectileBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UBoxComponent* projectileCollisionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* projectileNiagaraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* projectileMovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	EProjectileDamagePolicy projectileDamagePolicy = EProjectileDamagePolicy::OnHit;

	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle projectileDamageEffectSpecHandle;

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSpawnProjectileHitFx"))
	void BP_OnSpawnProjectileHitFX(const FVector& hitLocation);

private:
	void HandleApplyProjectileDamage(APawn* inHitPawn, const FGameplayEventData& inPayload);

	TArray<AActor*> overlappedActors;

};
