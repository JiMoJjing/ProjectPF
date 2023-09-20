
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
#include "Character/ActorComponents/CBasicAttackComponent.h"
#include "Character/ActorComponents/Status/CHpComponent.h"
#include "Character/ActorComponents/Status/CMpComponent.h"
#include "Character/ActorComponents/Status/COffenseComponent.h"
#include "Character/ActorComponents/Status/CDefenseComponent.h"
#include "Character/ActorComponents/Status/CSpeedComponent.h"
#include "Character/ActorComponents/CWeaponComponent.h"

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
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bDoCollisionTest = false;

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
		BasicAttackComponent = CreateDefaultSubobject<UCBasicAttackComponent>("BasicAttackComponent");
		HpComponent = CreateDefaultSubobject<UCHpComponent>("HpComponent");
		MpComponent = CreateDefaultSubobject<UCMpComponent>("MpComponent");
		OffenseComponent = CreateDefaultSubobject<UCOffenseComponent>("OffenseComponent");
		DefenseComponent = CreateDefaultSubobject<UCDefenseComponent>("DefenseComponent");
		SpeedComponent = CreateDefaultSubobject<UCSpeedComponent>("SpeedComponent");
		WeaponComponent = CreateDefaultSubobject<UCWeaponComponent>("WeaponComponent");
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
		AddTickPrerequisiteComponent(GetMesh());
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
		
	}
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
		EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Completed, this, &ACPlayableCharacterBase::LeftMouseClick);

		//LeftShift
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ACPlayableCharacterBase::RunActionPressed);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ACPlayableCharacterBase::RunActionReleased);
	}
}

void ACPlayableCharacterBase::Jump()
{
	if (!bCanMove)
		return;
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
	// bCanMove체크
	if (!bCanMove)
		return;

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
		if (!bMoving)
			bMoving = true;
		if (MoveEvent.IsBound())
			MoveEvent.Broadcast();
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
	bMoving = false;

	if (MoveEvent.IsBound())
		MoveEvent.Broadcast();
}

void ACPlayableCharacterBase::LeftMouseClick()
{
	BasicAttackComponent->DoAttack();
}

void ACPlayableCharacterBase::RunActionPressed()
{
	if (OnRunActionPressed.IsBound())
		OnRunActionPressed.Broadcast();
}

void ACPlayableCharacterBase::RunActionReleased()
{
	if (OnRunActionReleased.IsBound())
		OnRunActionReleased.Broadcast();
}


void ACPlayableCharacterBase::Test_Implementation()
{
	CLog::Print("TestSuccess", 3, 0.005f);
}

void ACPlayableCharacterBase::MoveForwardXY(float InSpeed)
{
	FVector forwardVector = GetActorForwardVector().GetSafeNormal2D();
	float speed = GetWorld()->GetDeltaSeconds() * InSpeed;
	AddActorWorldOffset(forwardVector * speed, true);
}

void ACPlayableCharacterBase::SetCharacterRotationYaw()
{
	float controlrotationYaw = GetBaseAimRotation().Yaw;
	FRotator rotation = GetActorRotation();

	rotation.Yaw = controlrotationYaw;

	SetActorRotation(rotation);
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


