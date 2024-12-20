// Vince Petrelli all Rights Reserved


#include "Characters/OMCharacterEnemy.h"
#include "GameFramework//CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Components/UI/OMEnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/OMWidgetBase.h"

// DebugHelper
#include "OMDebugHelper.h"

AOMCharacterEnemy::AOMCharacterEnemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	// Init Combat Component
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");

	// Init UI Component
	EnemyUIComponent = CreateDefaultSubobject<UOMEnemyUIComponent>("EnemyUIComponent");
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPawnCombatComponent* AOMCharacterEnemy::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AOMCharacterEnemy::GetPawnUICompoenent() const
{
	return EnemyUIComponent;
}

UOMEnemyUIComponent* AOMCharacterEnemy::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AOMCharacterEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Enemy HealthBar
	UOMWidgetBase* HealthWidget = Cast<UOMWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject());
	if (HealthWidget != nullptr)
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AOMCharacterEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AOMCharacterEnemy::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
		return;

	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(OMAbilitySystemComponent);
				}
			}
		)
	);
}
