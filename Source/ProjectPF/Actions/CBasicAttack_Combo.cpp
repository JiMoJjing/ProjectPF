#include "Actions/CBasicAttack_Combo.h"
#include "GameFramework/Character.h"
#include "Character/ActorComponents/CStateComponent.h"
#include "Character/ActorComponents/CWeaponComponent.h"

#include "Weapons/CWeapon.h"
#include "Weapons/CWeapon_Melee.h"
#include "Global.h"

void ACBasicAttack_Combo::DoAttack()
{
	Super::DoAttack();

	// TArray Data�� ��������� return
	if (Datas.Num() <= 0)
		return;
	// ComboEnable ���¿��� DoAttack�� ȣ��Ǹ� bComboStart�� True�� �ϰ� return
	if (bComboEnabled)
	{
		bComboEnabled = false;
		bComboStart = true;
		return;
	}
	// State Check
	if (StateComponent->GetState() > EPlayableCharacterState::Walking)
		return;
	// Set State
	StateComponent->SetState(EPlayableCharacterState::Attacking);
	// ComboIndex�� �´� Data�� �о�ͼ� ��Ÿ�� ����
	const FBasicAttackData& data = Datas[ComboIndex];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);
}

void ACBasicAttack_Combo::Begin_DoAttack()
{
	Super::Begin_DoAttack();
	// �޺� �Է��� ������ return
	if (!bComboStart)
		return;
	// ComboStart �ʱ�ȭ �� Index++
	bComboStart = false;
	ComboIndex++;
	// ���� ������� ��Ÿ�� ����
	OwnerCharacter->StopAnimMontage();
	// ComboIndex�� �´� Data�� �о�ͼ� ��Ÿ�� ����
	const FBasicAttackData& data = Datas[ComboIndex];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);
}

void ACBasicAttack_Combo::End_DoAttack()
{
	Super::End_DoAttack();
	//���۰� ����, �޺� ����
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

void ACBasicAttack_Combo::TraceStart()
{
	UKismetSystemLibrary::K2_SetTimer(this, "Trace", 0.01f, true);
}

void ACBasicAttack_Combo::TraceEnd()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "Trace");
	HittedActors.Empty();
}

void ACBasicAttack_Combo::Trace()
{
	ACWeapon_Melee* weapon = Cast<ACWeapon_Melee>(WeaponComponent->GetWeapon());

	if (weapon == nullptr)
	{
		CLog::Print("weapon nullptr");
		return;
	}

	FVector start = weapon->GetTraceStart();
	FVector end = weapon->GetTraceEnd();
	float radius = weapon->GetTraceRadius();

	if (UKismetSystemLibrary::SphereTraceSingle(
		this, start, end, radius
		, ETraceTypeQuery::TraceTypeQuery3
		, false
		, HittedActors
		, EDrawDebugTrace::ForDuration
		, Result
		, true
		, FLinearColor::Red
		, FLinearColor::Green
		, 1.f))
	{
		CLog::Print(Result.GetActor()->GetName());
		HittedActors.AddUnique(Result.GetActor());
	}

}
