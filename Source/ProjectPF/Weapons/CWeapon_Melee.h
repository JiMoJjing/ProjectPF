#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon.h"
#include "CWeapon_Melee.generated.h"


UCLASS()
class PROJECTPF_API ACWeapon_Melee : public ACWeapon
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintPure)
		FVector GetTraceStart();
	UFUNCTION(BlueprintPure)
		FVector GetTraceEnd();

	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetTraceRadius() { return Radius; }

};