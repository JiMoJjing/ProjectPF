#include "Character/ActorComponents/CBasicAttackComponent.h"
#include "Global.h"

#include "Character/CPlayableCharacterBase.h"
#include "Character/ActorComponents/CStateComponent.h"
#include "Actions/CDT_BasicAttack.h"
#include "Actions/CBasicAttack.h"

UCBasicAttackComponent::UCBasicAttackComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UCBasicAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACPlayableCharacterBase>(GetOwner());
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	
	if (!!BasicAttackDataTable)
		BasicAttackDataTable->BeginPlay(OwnerCharacter);
}


void UCBasicAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCBasicAttackComponent::DoAttack()
{
	BasicAttackDataTable->GetBasicAttackActor()->DoAttack();
}

