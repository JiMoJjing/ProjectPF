#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	class ACWeapon* GetWeapon() { return Weapon; }

private:
	UPROPERTY()
		class ACWeapon* Weapon;

	UPROPERTY(EditAnywhere)
		class UCDT_Weapon* WeaponData;

	ACharacter* OwnerCharacter;
};
