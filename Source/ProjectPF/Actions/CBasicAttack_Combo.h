#pragma once

#include "CoreMinimal.h"
#include "Actions/CBasicAttack.h"
#include "CBasicAttack_Combo.generated.h"


UCLASS()
class PROJECTPF_API ACBasicAttack_Combo : public ACBasicAttack
{
	GENERATED_BODY()
	

public:
	virtual void DoAttack() override;
	virtual void Begin_DoAttack() override;
	virtual void End_DoAttack() override;

	// AnimNotifyState_EnableCombo ���� ȣ���ϴ� �޺��Լ�
	void EnableCombo();
	void DisableCombo();

	// AnimNotifyState_Trace ���� ȣ���ϴ� Trace �Լ�
	void TraceStart();
	void TraceEnd();
	// Trace Start���� SetTimer�� ����� Trace�Լ�
	UFUNCTION(BlueprintCallable)
		void Trace();

	// ���� �� �� ���� ĳ������ RotationYaw�� ȸ����ų �Լ�
	UFUNCTION(BlueprintCallable)
		void SetCharacterRotationYaw();
private:
	uint32 ComboIndex = 0;

	bool bComboEnabled = false;
	bool bComboStart = false;

	UPROPERTY()
		TArray<AActor*> HittedActors;

	UPROPERTY()
		FHitResult Result;
};
