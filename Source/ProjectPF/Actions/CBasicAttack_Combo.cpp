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

	// TArray Data가 비어있으면 return
	if (Datas.Num() <= 0)
		return;
	// ComboEnable 상태에서 DoAttack이 호출되면 bComboStart를 True로 하고 return
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
	// ComboIndex에 맞는 Data를 읽어와서 몽타주 실행
	const FBasicAttackData& data = Datas[ComboIndex];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);
}

void ACBasicAttack_Combo::Begin_DoAttack()
{
	Super::Begin_DoAttack();
	// 콤보 입력이 없으면 return
	if (!bComboStart)
		return;
	// ComboStart 초기화 및 Index++
	bComboStart = false;
	ComboIndex++;
	// 지금 재생중인 몽타주 멈춤
	OwnerCharacter->StopAnimMontage();
	// ComboIndex에 맞는 Data를 읽어와서 몽타주 실행
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
