#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/CDT_Weapon.h"
#include "CWeapon.generated.h"

UCLASS()
class PROJECTPF_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetWeaponData(const FWeaponData& InData);
	void SetRadius(float InRadius) { Radius = InRadius; }

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USceneComponent* DefaultSceneComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float Radius;

};
