#include "Actions/CBasicAttack.h"
#include "GameFramework/Character.h"
#include "Character/ActorComponents/CStateComponent.h"

ACBasicAttack::ACBasicAttack()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACBasicAttack::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	StateComponent = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
}

void ACBasicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

