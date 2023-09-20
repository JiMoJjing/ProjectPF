#include "Actions/CBasicAttack.h"
#include "GameFramework/Character.h"
#include "Character/ActorComponents/CWeaponComponent.h"
#include "Character/ActorComponents/CStateComponent.h"
#include "Character/CPlayableCharacterBase.h"
#include "Weapons/CWeapon.h"

ACBasicAttack::ACBasicAttack()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACBasicAttack::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACPlayableCharacterBase>(GetOwner());
	StateComponent = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	WeaponComponent = Cast<UCWeaponComponent>(OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass()));

}

void ACBasicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

