// Vince Petrelli all Rights Reserved


#include "Characters/OMCharacterBase.h"
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "AbilitySystem/OMAttributeSet.h"

// Sets default values
AOMCharacterBase::AOMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;



	/*******************************
		 Init GameAbilitySystem
	********************************/
	OMAbilitySystemComponent = CreateDefaultSubobject<UOMAbilitySystemComponent>(TEXT("OMAbilitySystemComponent"));
	OMAttributeSet = CreateDefaultSubobject<UOMAttributeSet>(TEXT("OMAttributeSet"));
}


// GetAbilitySystemCompoenent
UAbilitySystemComponent* AOMCharacterBase::GetAbilitySystemComponent() const
{
	return GetOMAbilitySystemComponent();
}

// GetPawnCombatComponent just for Override
UPawnCombatComponent* AOMCharacterBase::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AOMCharacterBase::GetPawnUICompoenent() const
{
	return nullptr;
}


/********************************
	Set AbilitySystem's Owner
*********************************/
void AOMCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Set AbilitySystem's Owner
	if (OMAbilitySystemComponent)
	{
		OMAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}


