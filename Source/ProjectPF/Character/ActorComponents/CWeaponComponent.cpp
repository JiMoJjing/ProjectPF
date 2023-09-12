#include "Character/ActorComponents/CWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/CWeapon.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	FTransform transform;

	if (WeaponData == nullptr)
		return;

	if (!!WeaponData->GetWeaponClass())
	{
		Weapon = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACWeapon>(WeaponData->GetWeaponClass(), transform, OwnerCharacter);
		Weapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponData->WeaponData.SocketName);
		Weapon->SetActorLabel("WeaponActor");
		Weapon->SetWeaponData(WeaponData->WeaponData);
		UGameplayStatics::FinishSpawningActor(Weapon, transform);
	}
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

