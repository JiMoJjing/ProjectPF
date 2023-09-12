#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CDT_Weapon.generated.h"


USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
        class USkeletalMesh* Mesh;

    UPROPERTY(EditAnywhere)
        FVector RelativeLocation;

    UPROPERTY(EditAnywhere)
        FRotator RelativeRotation;

    UPROPERTY(EditAnywhere)
        FVector Scale = FVector(1,1,1);

    UPROPERTY(EditAnywhere)
        FName SocketName = "";

    UPROPERTY(EditAnywhere)
        float Radius = 0.f;
};


UCLASS()
class PROJECTPF_API UCDT_Weapon : public UDataAsset
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
        TSubclassOf<class ACWeapon> GetWeaponClass() { return WeaponClass; }
	
public:
    UPROPERTY(EditAnywhere)
        TSubclassOf<class ACWeapon> WeaponClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        FWeaponData WeaponData;
};
