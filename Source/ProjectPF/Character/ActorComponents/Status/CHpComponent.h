#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CHpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCHpComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter 함수들 블루프린트에서 사용할 것도 염두에두었다. */
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
	//플레이어의 기본 Hp Max
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float BaseHpMax;
	// Lv당 상승 Hp Max
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float HpMaxPerLv;
	//장비나 버프로 인한 HP, MP Max 상승량 관리
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float AddedHpMax = 0.f;
	//Base + Added 합쳐 최종 HP Max 관리
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float FinalHpMax;
	//현재 HP, MP
	UPROPERTY(EditDefaultsOnly, Category = "Hp")
		float NowHp;

	//현재 Level
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
