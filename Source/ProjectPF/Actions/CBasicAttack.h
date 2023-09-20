#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CDT_BasicAttack.h"
#include "CBasicAttack.generated.h"

UCLASS()
class PROJECTPF_API ACBasicAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBasicAttack();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void SetDatas(TArray<FBasicAttackData> InDatas) { Datas = InDatas; }

	virtual void DoAttack() {}
	virtual void Begin_DoAttack() {}
	virtual void End_DoAttack() {}

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACPlayableCharacterBase* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* StateComponent;
	UPROPERTY(BlueprintReadOnly)
		class UCWeaponComponent* WeaponComponent;


	//class ACWeapon* Weapon;
	TArray<FBasicAttackData> Datas;
};
