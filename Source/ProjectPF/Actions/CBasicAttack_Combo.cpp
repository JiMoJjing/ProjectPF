#include "Actions/CBasicAttack_Combo.h"
#include "GameFramework/Character.h"
#include "Character/ActorComponents/CStateComponent.h"
#include "Global.h"

void ACBasicAttack_Combo::DoAttack()
{
	Super::DoAttack();

	if (Datas.Num() <= 0)
		return;

	if (bComboEnabled)
	{
		bComboEnabled = false;
		bComboStart = true;
		return;
	}

	if ((int)StateComponent->GetState() > 1)
		return;

	StateComponent->SetState(EPlayableCharacterState::Attacking);

	const FBasicAttackData& data = Datas[ComboIndex];

	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);
}

void ACBasicAttack_Combo::Begin_DoAttack()
{
	Super::Begin_DoAttack();

	if (!bComboStart)
		return;


	bComboStart = false;
	ComboIndex++;

	OwnerCharacter->StopAnimMontage();

	const FBasicAttackData& data = Datas[ComboIndex];

	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);
}

void ACBasicAttack_Combo::End_DoAttack()
{
	Super::End_DoAttack();
	//동작과 상태, 콤보 리셋
	ComboIndex = 0;
	OwnerCharacter->StopAnimMontage();
	StateComponent->SetState(EPlayableCharacterState::Idle);
}

void ACBasicAttack_Combo::EnableCombo()
{
	bComboEnabled = true;
}

void ACBasicAttack_Combo::DisableCombo()
{
	bComboEnabled = false;
}
