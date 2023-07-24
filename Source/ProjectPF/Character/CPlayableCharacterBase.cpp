
#include "Character/CPlayableCharacterBase.h"

#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "UObject/ConstructorHelpers.h"
#include "Character/CharacterDataAssets/CDA_CharacterBase.h"

#include "Utilities/CLog.h"


ACPlayableCharacterBase::ACPlayableCharacterBase()
{
	// Tick
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	//GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	// C++에서 직접 skeletal mesh와 anim blueprint 를 참조하는걸 지양하는듯?
	/*ConstructorHelpers::FObjectFinder<USkeletalMesh> Body(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	if(Body.Succeeded())
		GetMesh()->SetSkeletalMeshAsset(Body.Object);*/
	/*TSubclassOf<UAnimInstance> animinstance;
	ConstructorHelpers::FClassFinder<UAnimInstance> Anim(TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C'"));
	if (Anim.Succeeded())
	{
		animinstance = Anim.Class;
		GetMesh()->SetAnimInstanceClass(animinstance);
	}*/


}

void ACPlayableCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(CharacterBaseDataAsset))
	{
		// Transform
		GetMesh()->SetSkeletalMeshAsset(CharacterBaseDataAsset->SkeletalMesh);
		GetMesh()->SetRelativeTransform(CharacterBaseDataAsset->Mesh);
		GetMesh()->SetAnimInstanceClass(CharacterBaseDataAsset->AnimInstanceClass);
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	/*
	if (IICharacter* interfacetest = Cast<IICharacter>(this))
		interfacetest->Test_Implementation();
	*/
}

void ACPlayableCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACPlayableCharacterBase::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACPlayableCharacterBase::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPlayableCharacterBase::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayableCharacterBase::Look);

		//LeftMouseClick
		EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Triggered, this, &ACPlayableCharacterBase::LeftMouseClick);

	}
}

void ACPlayableCharacterBase::Jump()
{
	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;
}

void ACPlayableCharacterBase::StopJumping()
{
	bPressedJump = false;
	ResetJumpState();
}

void ACPlayableCharacterBase::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACPlayableCharacterBase::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACPlayableCharacterBase::LeftMouseClick()
{
	CLog::Print("Left Mouse Clicked!", 0, 5.f);
}

void ACPlayableCharacterBase::Test_Implementation()
{
	CLog::Print("TestSuccess");
}

void ACPlayableCharacterBase::ChangeBindingAction(UInputAction* InAction, FKey InKey)
{
	DefaultMappingContext->UnmapAllKeysFromAction(InAction);
	DefaultMappingContext->MapKey(InAction, InKey);
}

void ACPlayableCharacterBase::Jump2(FKey PressedKey) 
{
	CLog::Print((PressedKey.ToString()));
	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;
}

void ACPlayableCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


