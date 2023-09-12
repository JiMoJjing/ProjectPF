#include "Weapons/CWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Global.h"


ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>("DefalutSceneComponent");
	if (!!DefaultSceneComponent)
		SetRootComponent(DefaultSceneComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	if (!!SkeletalMesh)
		SkeletalMesh->SetupAttachment(DefaultSceneComponent);

}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACWeapon::SetWeaponData(const FWeaponData& InData)
{
	SkeletalMesh->SetSkeletalMeshAsset(InData.Mesh);
	SkeletalMesh->SetRelativeLocation(InData.RelativeLocation);
	SkeletalMesh->SetRelativeRotation(InData.RelativeRotation);
	SkeletalMesh->SetWorldScale3D(InData.Scale);
	Radius = InData.Radius;
}

