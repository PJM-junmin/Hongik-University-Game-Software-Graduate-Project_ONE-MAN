
// Vince Petrelli all Rights Reserved


#include "Characters/OMCharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Input
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/OMInputComponent.h"
#include "OMGameplayTags.h"

// AbilitySystem
#include "AbilitySystem/OMAbilitySystemComponent.h"
#include "AbilitySystem/OMAttributeSet.h"
#include "DataAssets/StartUpData/DataAsset_PlayerStartUpData.h"

// Combat
#include "Components/Combat/OMPlayerCombatComponent.h"

// IK
#include "Components/IK/OM_FootIK.h"

// UI
#include "Components/UI/OMPlayerUIComponent.h"

// DebugHelper
#include "OMDebugHelper.h"


AOMCharacterPlayer::AOMCharacterPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// InitCameraComponent
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 00.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// InitCharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;


	// InitCombatComponent
	PlayerCombatComponent = CreateDefaultSubobject<UOMPlayerCombatComponent>(TEXT("OMPlayerCombatComponent"));

	// InitFootIKComponent
	PlayerFootIKComponent = CreateDefaultSubobject<UOM_FootIK>(TEXT("OMFootIKComponent"));

	// InitUIComponent
	OMPlayerUIComponent = CreateDefaultSubobject<UOMPlayerUIComponent>(TEXT("OMPlayerUIComponent"));

	// Init SkeletalMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT
	("/Script/Engine.SkeletalMesh'/Game/AssetSource/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Forge.SK_CharM_Forge'"));
	if (CharacterMeshRef.Object != nullptr)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -96.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	// Init AnimInstance
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT
	("/Script/Engine.AnimBlueprint'/Game/PlayerCharacter/Animation/ABP_Player.ABP_Player_C'"));
	if (AnimInstanceClassRef.Class != nullptr)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// Init InputData ActionMapingContext
	static ConstructorHelpers::FObjectFinder<UDataAsset_InputConfig> InputConfigDataAssetRef(TEXT
	("/Script/ONEMAN.DataAsset_InputConfig'/Game/PlayerCharacter/DA_InputConfig.DA_InputConfig'"));
	if (InputConfigDataAssetRef.Object != nullptr)
	{
		InputConfigDataAsset = InputConfigDataAssetRef.Object;
	}

	// Init GamePlayAbility of StartUpData
	static ConstructorHelpers::FObjectFinder<UDataAsset_StartUpDataBase> CharacterStartUpDataAssetRef(TEXT
	("/Script/ONEMAN.DataAsset_PlayerStartUpData'/Game/PlayerCharacter/DA_Player.DA_Player'"));
	if (CharacterStartUpDataAssetRef.Object != nullptr)
	{
		CharacterStartUpData = CharacterStartUpDataAssetRef.Object;
	}
}

UPawnCombatComponent* AOMCharacterPlayer::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

UPawnUIComponent* AOMCharacterPlayer::GetPawnUICompoenent() const
{
	return OMPlayerUIComponent;
}

UOMPlayerUIComponent* AOMCharacterPlayer::GetPlayerUIComponent() const
{
	return OMPlayerUIComponent;
}


// GetAbilitySystemCompoenent
void AOMCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/*if (OMAbilitySystemComponent != nullptr && OMAttributeSet != nullptr)
	{
		// If Successed Print Owner's Name
		const FString ASCText = FString::Printf(TEXT("OwnerActor: %s, AvatarActor: %s"),
			*OMAbilitySystemComponent->GetOwnerActor()->GetActorLabel(),
			*OMAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
		Debug::Print(TEXT("Successed Set AblitySystem") + ASCText, FColor::Green);
		Debug::Print(TEXT("Successed Set AttributeSet") + ASCText, FColor::Green);
		Debug::Print(TEXT("CreateOMCharacterPlayer"));
	}
	*/

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(OMAbilitySystemComponent);
		}
	}
}


/*************************************
			 Binding Input
**************************************/
void AOMCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =  ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	// if Subsystem is not valid
	check(Subsystem);
	
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	UOMInputComponent* OMInputComponent = CastChecked<UOMInputComponent>(PlayerInputComponent);
	if (OMInputComponent != nullptr)
	{
		// NativeInputSection
		OMInputComponent->BindNativeInputAction(InputConfigDataAsset, OMGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AOMCharacterPlayer::Look);
		OMInputComponent->BindNativeInputAction(InputConfigDataAsset, OMGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AOMCharacterPlayer::Move);

		//AbilityInputSection
		OMInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	}
}

void AOMCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}


/*************************************
		 Movement Section
**************************************/
void AOMCharacterPlayer::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.0f)
	{
		AddControllerYawInput(-LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AOMCharacterPlayer::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

/*************************************
		 Input_AbilitySection
**************************************/
void AOMCharacterPlayer::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	OMAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AOMCharacterPlayer::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	OMAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
