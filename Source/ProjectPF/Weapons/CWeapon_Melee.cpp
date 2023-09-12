#include "Weapons/CWeapon_Melee.h"
#include "Global.h"

void ACWeapon_Melee::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACWeapon_Melee::Tick(float DeltaTime)
{

}

FVector ACWeapon_Melee::GetTraceStart()
{
	FVector Start = SkeletalMesh->GetSocketLocation("Start");
	return Start;
}

FVector ACWeapon_Melee::GetTraceEnd()
{
	FVector End = SkeletalMesh->GetSocketLocation("End");
	return End;
}
