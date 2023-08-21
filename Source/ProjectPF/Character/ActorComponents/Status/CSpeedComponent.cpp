
#include "Character/ActorComponents/Status/CSpeedComponent.h"
#include "Character/CPlayableCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Character/ActorComponents/CStatusComponent.h"
#include "Character/ActorComponents/CLevelComponent.h"
#include "Global.h"

UCSpeedComponent::UCSpeedComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCSpeedComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACPlayableCharacterBase>(GetOwner());

	// StatusComponent 
	{
		UCStatusComponent* StatusComponent = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
		if (StatusComponent)
		{
			FStatusDataTable data;
			data = StatusComponent->GetStatusData();

			SetBaseWalkSpeed(data.WalkSpeed);
			SetBaseRunSpeed(data.RunSpeed);
		}
	}

	SetFinalWalkSpeed();
	SetFinalRunSpeed();

	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = FinalWalkSpeed;

}

void UCSpeedComponent::SetAddedWalkSpeed()
{
}

void UCSpeedComponent::SetFinalWalkSpeed()
{
	FinalWalkSpeed = BaseWalkSpeed + AddedWalkSpeed;
}

void UCSpeedComponent::SetAddedRunSpeed()
{
}

void UCSpeedComponent::SetFinalRunSpeed()
{
	FinalRunSpeed = BaseRunSpeed + AddedRunSpeed;
}


void UCSpeedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

