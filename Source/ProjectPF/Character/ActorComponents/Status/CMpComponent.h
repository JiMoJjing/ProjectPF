#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMpComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTPF_API UCMpComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter �Լ��� �������Ʈ���� ����� �͵� ���ο��ξ���. */
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
	//�÷��̾��� �⺻ Mp Max
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float BaseMpMax;
	// Lv�� ��� Mp Max
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float MpMaxPerLv;
	//��� ������ ���� Mp, MP Max ��·� ����
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float AddedMpMax = 0.f;
	//Base + Added ���� ���� Mp Max ����
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float FinalMpMax;
	//���� Mp, MP
	UPROPERTY(EditDefaultsOnly, Category = "Mp")
		float NowMp;

	//���� Level
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