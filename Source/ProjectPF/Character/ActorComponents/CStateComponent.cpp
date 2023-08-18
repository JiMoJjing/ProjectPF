#include "Character/ActorComponents/CStateComponent.h"
#include "Global.h"

#include "Character/CPlayableCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

UCStateComponent::UCStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACPlayableCharacterBase>(GetOwner());

	OwnerCharacter->OnMoveEvent().AddUFunction(this, "StateCheck");
	//OwnerCharacter->OnMoveEvent().AddUObject(this, &UCStateComponent::StateCheck);

	OwnerCharacter->MovementModeChangedDelegate.AddDynamic(this, &UCStateComponent::MovementModeChangedBind);
}

void UCStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCStateComponent::SetState(EPlayableCharacterState InState)
{
	EPlayableCharacterState prevState = State;
	State = InState;

	if (prevState == State)
		return;

	if (OnStateChanged.IsBound())
		OnStateChanged.Broadcast(prevState, State);
}

void UCStateComponent::StateCheck()
{
	if (OwnerCharacter->GetCharacterMovement()->IsFalling())
	{
		SetState(EPlayableCharacterState::Jumping);
		return;
	}

	if (!(OwnerCharacter->bMoving))
	{
		SetState(EPlayableCharacterState::Idle);
		return;
	}

	float speed = OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed;

	if (UKismetMathLibrary::NearlyEqual_FloatFloat(speed, 200.f, 1.f))
		SetState(EPlayableCharacterState::Walking);
	else if (UKismetMathLibrary::NearlyEqual_FloatFloat(speed, 600.f, 1.f))
		SetState(EPlayableCharacterState::Running);
}

void UCStateComponent::MovementModeChangedBind(ACharacter* InCharacter, EMovementMode InPrevMovementMode, uint8 InPrevCustomMovementMode)
{
	EMovementMode newMovementMode = InCharacter->GetCharacterMovement()->MovementMode;

	switch (newMovementMode)
	{
	case MOVE_None: break;
	case MOVE_Walking: StateCheck(); break;
	case MOVE_NavWalking: break;
	case MOVE_Falling: StateCheck(); break;
	case MOVE_Swimming: break;
	case MOVE_Flying: break;
	case MOVE_Custom: break;
	case MOVE_MAX: break;
	default: break;
	}
}


