
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

#include "Character/ActorComponents/CStateComponent.h"
#include "Character/ActorComponents/CStatusComponent.h"
#include "Character/ActorComponents/CLevelComponent.h"
#include "Character/ActorComponents/Status/CHpComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Character/CharacterDataAssets/CDA_CharacterBase.h"

#include "Global.h"



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
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
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

	//ActorComponent
	{
		StateComponent = CreateDefaultSubobject<UCStateComponent>("StateComponent");
		StatusComponent = CreateDefaultSubobject<UCStatusComponent>("StatusComponent");
		LevelComponent = CreateDefaultSubobject<UCLevelComponent>("LevelComponent");
		HpComponent = CreateDefaultSubobject<UCHpComponent>("HpComponent");
	}

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

	//DELEGATE Binding
	{
		if(IsValid(StateComponent))
			StateComponent->OnStateChanged.AddDynamic(this, &ACPlayableCharacterBase::OnStateChanged);

		MovementModeChangedDelegate.AddDynamic(this, &ACPlayableCharacterBase::MovementModeChangedBind);
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	//Status 초기화
	{
		HpComponent->SetBaseHpMax(StatusComponent->GetStatusData().HpMax);
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ACPlayableCharacterBase::MoveStart);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACPlayableCharacterBase::MoveEnd);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayableCharacterBase::Look);

		//LeftMouseClick
		EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Triggered, this, &ACPlayableCharacterBase::LeftMouseClick);

		//LeftShift
		EnhancedInputComponent->BindAction(LeftShiftAction, ETriggerEvent::Started, this, &ACPlayableCharacterBase::LeftShiftPressed);
		EnhancedInputComponent->BindAction(LeftShiftAction, ETriggerEvent::Completed, this, &ACPlayableCharacterBase::LeftShiftReleased);
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

	//내가 추가한 코드
	{
		OnMoveStateChanged();
		if (!bMove)
			bMove = true;
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

void ACPlayableCharacterBase::MoveStart()
{
	
}

void ACPlayableCharacterBase::MoveEnd()
{
	bMove = false;
	OnMoveStateChanged();
}

void ACPlayableCharacterBase::LeftMouseClick()
{
	//CLog::Print("Left Mouse Clicked!", 0, 5.f);
}

void ACPlayableCharacterBase::LeftShiftPressed()
{
	//Shift Pressed 시 Running 됨.
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	CLog::Print("Shift Pressed", 0, 1.f);
}

void ACPlayableCharacterBase::LeftShiftReleased()
{
	//Shift Released 시 Walking 됨.
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	CLog::Print("Shift Released", 0, 1.f);
}

void ACPlayableCharacterBase::MovementModeChangedBind(ACharacter* InCharacter, EMovementMode InPrevMovementMode, uint8 InPrevCustomMovementMode)
{
	EMovementMode newMovementMode = InCharacter->GetCharacterMovement()->MovementMode;

	switch (newMovementMode)
	{
	case MOVE_None: break;
	case MOVE_Walking: OnMoveStateChanged(); break;
	case MOVE_NavWalking: break;
	case MOVE_Falling: OnMoveStateChanged(); break;
	case MOVE_Swimming: break;
	case MOVE_Flying: break;
	case MOVE_Custom: break;
	case MOVE_MAX: break;
	default: break;
	}
}

void ACPlayableCharacterBase::OnMoveStateChanged()
{
	if (GetCharacterMovement()->IsFalling())
	{
		StateComponent->SetState(EPlayableCharacterState::Jumping);
		return;
	}

	if (!bMove)
	{
		StateComponent->SetState(EPlayableCharacterState::Idle);
		return;
	}

	float speed = GetCharacterMovement()->MaxWalkSpeed;

	if (UKismetMathLibrary::NearlyEqual_FloatFloat(speed, WalkingSpeed, 1.f))
		StateComponent->SetState(EPlayableCharacterState::Walking);
	else if (UKismetMathLibrary::NearlyEqual_FloatFloat(speed, RunningSpeed, 1.f))
		StateComponent->SetState(EPlayableCharacterState::Running);
}

void ACPlayableCharacterBase::OnStateChanged_Implementation(EPlayableCharacterState InPrevState, EPlayableCharacterState InNewState)
{
	switch (InNewState)
	{
	case EPlayableCharacterState::Idle: break;
	case EPlayableCharacterState::Walking: SetWalkingMode(); break;
	case EPlayableCharacterState::Running: SetRunningMode(); break;
	case EPlayableCharacterState::Jumping: break;
	case EPlayableCharacterState::Attacking: break;
	case EPlayableCharacterState::Casting: break;
	default: break;
	}
}

void ACPlayableCharacterBase::SetWalkingMode()
{
	//CLog::Print("Walking Mode Call", 4, 1.f, FColor::Red);
}

void ACPlayableCharacterBase::SetRunningMode()
{
	//CLog::Print("Running Mode Call", 4, 1.f, FColor::Red);
}

void ACPlayableCharacterBase::Test_Implementation()
{
	CLog::Print("TestSuccess", 3, 0.005f);
}

void ACPlayableCharacterBase::ChangeBindingAction(UInputAction* InAction, FKey InKey)
{
	DefaultMappingContext->UnmapAllKeysFromAction(InAction);
	DefaultMappingContext->MapKey(InAction, InKey);
}


void ACPlayableCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


