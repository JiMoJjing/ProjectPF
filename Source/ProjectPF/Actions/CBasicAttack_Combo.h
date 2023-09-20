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

	// AnimNotifyState_EnableCombo 에서 호출하는 콤보함수
	void EnableCombo();
	void DisableCombo();

	// AnimNotifyState_Trace 에서 호출하는 Trace 함수
	void TraceStart();
	void TraceEnd();
	// Trace Start에서 SetTimer에 등록할 Trace함수
	UFUNCTION(BlueprintCallable)
		void Trace();

	// 공격 할 때 마다 캐릭터의 RotationYaw를 회전시킬 함수
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
