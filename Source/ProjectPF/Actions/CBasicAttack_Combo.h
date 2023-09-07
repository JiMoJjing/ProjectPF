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

	void EnableCombo();
	void DisableCombo();

private:
	uint32 ComboIndex = 0;

	bool bComboEnabled = false;
	bool bComboStart = false;
};
