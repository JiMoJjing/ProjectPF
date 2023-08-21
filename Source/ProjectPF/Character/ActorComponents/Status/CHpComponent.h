#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CHpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCHpComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter �Լ��� �������Ʈ���� ����� �͵� ���ο��ξ���. */
	UFUNCTION(BlueprintPure, Category = "Hp")
		FORCEINLINE float GetBaseHpMax() { return BaseHpMax; }

	UFUNCTION(BlueprintPure, Category = "Hp")
		FORCEINLINE float GetAddedHpMax() { return AddedHpMax; }

	UFUNCTION(BlueprintPure, Category = "Hp")
		FORCEINLINE float GetFinalHpMax() { return FinalHpMax; }

	UFUNCTION(BlueprintPure, Category = "Hp")
		FORCEINLINE float GetNowHp() { return NowHp; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsHpFull() { return NowHp == FinalHpMax; }

private:
	//�÷��̾��� �⺻ Hp Max
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float BaseHpMax;
	// Lv�� ��� Hp Max
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float HpMaxPerLv;
	//��� ������ ���� HP, MP Max ��·� ����
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float AddedHpMax = 0.f;
	//Base + Added ���� ���� HP Max ����
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float FinalHpMax;
	//���� HP, MP
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float NowHp;

	//���� Level
	UPROPERTY(EditDefaultsOnly, Category = "Level")
		int32 Level;


public:
	UFUNCTION(BlueprintCallable, Category = "Hp")
		void SetBaseHpMax(float InHpMax) { BaseHpMax = InHpMax; }

	UFUNCTION(BlueprintCallable, Category = "Hp")
		void SetHpMaxPerLv(float InHpMaxPerLv) { HpMaxPerLv = InHpMaxPerLv; }

	UFUNCTION(BlueprintCallable, Category = "Hp")
		void SetAddedHpMax();

	UFUNCTION(BlueprintCallable, Category = "Hp")
		void SetFinalHpMax();

	UFUNCTION(BlueprintCallable, Category = "Hp")
		void SetNowHp(float InFloat);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void SetLevel(int32 inLevel);

private:
	class ACPlayableCharacterBase* OwnerCharacter;

public:	
	UCHpComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
