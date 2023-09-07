#include "Actions/AnimNotifies/CANS_EnableCombo.h"

#include "Character/ActorComponents/CBasicAttackComponent.h"
#include "Actions/CBasicAttack_Combo.h"
#include "Actions/CDT_BasicAttack.h"

#include "Global.h"

FString UCANS_EnableCombo::GetNotifyName_Implementation() const
{
	return "Enable Combo";
}

void UCANS_EnableCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if (MeshComp == nullptr)
		return;
	if (MeshComp->GetOwner() == nullptr)
		return;

	UCBasicAttackComponent* component = Cast<UCBasicAttackComponent>(MeshComp->GetOwner()->GetComponentByClass(UCBasicAttackComponent::StaticClass()));
	if (component == nullptr)
		return;
	ACBasicAttack_Combo* actor = Cast<ACBasicAttack_Combo>(component->GetBasicAttackDataTable()->GetBasicAttackActor());
	if (actor == nullptr)
		return;

	actor->EnableCombo();
}

void UCANS_EnableCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == nullptr)
		return;
	if (MeshComp->GetOwner() == nullptr)
		return;

	UCBasicAttackComponent* component = Cast<UCBasicAttackComponent>(MeshComp->GetOwner()->GetComponentByClass(UCBasicAttackComponent::StaticClass()));
	if (component == nullptr)
		return;

	ACBasicAttack_Combo* actor = Cast<ACBasicAttack_Combo>(component->GetBasicAttackDataTable()->GetBasicAttackActor());
	if (actor == nullptr)
		return;

	actor->DisableCombo();
}