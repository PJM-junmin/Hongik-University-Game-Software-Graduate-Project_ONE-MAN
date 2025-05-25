// Vince Petrelli all Rights Reserved


#include "Characters/OMCharacterEnemy.h"
#include "GameFramework//CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Components/UI/OMEnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/OMWidgetBase.h"
#include "Components/BoxComponent.h"
#include "OMFunctionLibrary.h"
#include "GameModes/OMGameModeBase.h"

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
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	// Init Combat Component
	enemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");

	// Init UI Component
	enemyUIComponent = CreateDefaultSubobject<UOMEnemyUIComponent>("EnemyUIComponent");
	enemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");
	enemyHealthWidgetComponent->SetupAttachment(GetMesh());

	leftFootCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftFootCollisionBox");
	leftFootCollisionBox->SetupAttachment(GetMesh());
	leftFootCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	leftFootCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	rightFootCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightFootCollisionBox");
	rightFootCollisionBox->SetupAttachment(GetMesh());
	rightFootCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	rightFootCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
}

UPawnCombatComponent* AOMCharacterEnemy::GetPawnCombatComponent() const
{
	return enemyCombatComponent;
}

UPawnUIComponent* AOMCharacterEnemy::GetPawnUICompoenent() const
{
	return enemyUIComponent;
}

UOMEnemyUIComponent* AOMCharacterEnemy::GetEnemyUIComponent() const
{
	return enemyUIComponent;
}

void AOMCharacterEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Enemy HealthBar
	UOMWidgetBase* HealthWidget = Cast<UOMWidgetBase>(enemyHealthWidgetComponent->GetUserWidgetObject());
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

#if WITH_EDITOR
void AOMCharacterEnemy::PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent)
{
	Super::PostEditChangeProperty(propertyChangedEvent);

	if (propertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, leftFootCollisionBoxAttachBoneName))
	{
		leftFootCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, leftFootCollisionBoxAttachBoneName);
	}

	if (propertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, rightFootCollisionBoxAttachBoneName))
	{
		rightFootCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, rightFootCollisionBoxAttachBoneName);
	}

}
#endif

void AOMCharacterEnemy::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* hitPawn = Cast<APawn>(OtherActor))
	{
		if (UOMFunctionLibrary::IsTargetPawnHostile(this, hitPawn))
		{
			enemyCombatComponent->OnHitTargetActor(hitPawn);
		}
	}
}

void AOMCharacterEnemy::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
		return;

	int32 abilityApplyLevel = 1;

	if (AOMGameModeBase* baseGameMode = GetWorld()->GetAuthGameMode<AOMGameModeBase>())
	{
		switch (baseGameMode->GetCurrentGameDifficulty())
		{
		case EOMGameDifficulty::Easy:
			abilityApplyLevel = 1;
			break;

		case EOMGameDifficulty::Normal:
			abilityApplyLevel = 2;
			break;

		case EOMGameDifficulty::Hard:
			abilityApplyLevel = 3;
			break;

		case EOMGameDifficulty::Impossible:
			abilityApplyLevel = 4;
			break;

		default:
			break;
		}
	}
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, abilityApplyLevel]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(OMAbilitySystemComponent, abilityApplyLevel);
				}
			}
		)
	);
}
