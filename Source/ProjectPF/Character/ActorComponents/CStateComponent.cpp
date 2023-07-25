#include "Character/ActorComponents/CStateComponent.h"
#include "Global.h"



UCStateComponent::UCStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCStateComponent::SetState(EPlayableCharacterState InState)
{
	EPlayableCharacterState prevState = State;
	State = InState;

	if (OnStateChanged.IsBound())
		OnStateChanged.Broadcast(prevState, State);
}
