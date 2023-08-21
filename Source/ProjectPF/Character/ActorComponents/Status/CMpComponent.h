#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMpComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTPF_API UCMpComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter 함수들 블루프린트에서 사용할 것도 염두에두었다. */
	UFUNCTION(BlueprintPure, Category = "Mp")
		FORCEINLINE float GetBaseMpMax() { return BaseMpMax; }

	UFUNCTION(BlueprintPure, Category = "Mp")
		FORCEINLINE float GetAddedMpMax() { return AddedMpMax; }

	UFUNCTION(BlueprintPure, Category = "Mp")
		FORCEINLINE float GetFinalMpMax() { return FinalMpMax; }

	UFUNCTION(BlueprintPure, Category = "Mp")
		FORCEINLINE float GetNowMp() { return NowMp; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsMpFull() { return NowMp == FinalMpMax; }

private:
	//플레이어의 기본 Mp Max
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float BaseMpMax;
	// Lv당 상승 Mp Max
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float MpMaxPerLv;
	//장비나 버프로 인한 Mp, MP Max 상승량 관리
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float AddedMpMax = 0.f;
	//Base + Added 합쳐 최종 Mp Max 관리
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float FinalMpMax;
	//현재 Mp, MP
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float NowMp;

	//현재 Level
	UPROPERTY(EditDefaultsOnly, Category = "Level")
		int32 Level;


public:
	UFUNCTION(BlueprintCallable, Category = "Mp")
		void SetBaseMpMax(float InMpMax) { BaseMpMax = InMpMax; }

	UFUNCTION(BlueprintCallable, Category = "Mp")
		void SetMpMaxPerLv(float InMpMaxPerLv) { MpMaxPerLv = InMpMaxPerLv; }

	UFUNCTION(BlueprintCallable, Category = "Mp")
		void SetAddedMpMax();

	UFUNCTION(BlueprintCallable, Category = "Mp")
		void SetFinalMpMax();

	UFUNCTION(BlueprintCallable, Category = "Mp")
		void SetNowMp(float InFloat);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void SetLevel(int32 inLevel);

private:
	class ACPlayableCharacterBase* OwnerCharacter;

public:
	UCMpComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};