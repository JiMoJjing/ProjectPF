#include "Actions/CBasicAttack.h"
#include "GameFramework/Character.h"
#include "Character/ActorComponents/CWeaponComponent.h"
#include "Character/ActorComponents/CStateComponent.h"

#include "Weapons/CWeapon.h"

ACBasicAttack::ACBasicAttack()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACBasicAttack::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	StateComponent = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	WeaponComponent = Cast<UCWeaponComponent>(OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass()));

	//Weapon = WeaponComponent->GetWeapon();
}

void ACBasicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

