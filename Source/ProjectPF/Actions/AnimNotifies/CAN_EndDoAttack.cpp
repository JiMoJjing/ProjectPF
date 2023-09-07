#include "Actions/AnimNotifies/CAN_EndDoAttack.h"

#include "Character/ActorComponents/CBasicAttackComponent.h"
#include "Actions/CBasicAttack.h"
#include "Actions/CDT_BasicAttack.h"


FString UCAN_EndDoAttack::GetNotifyName_Implementation() const
{
	return "EndAttack";
}

void UCAN_EndDoAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr)
		return;
	if (MeshComp->GetOwner() == nullptr)
		return;

	UCBasicAttackComponent* component = Cast<UCBasicAttackComponent>(MeshComp->GetOwner()->GetComponentByClass(UCBasicAttackComponent::StaticClass()));
	if (component == nullptr)
		return;

	component->GetBasicAttackDataTable()->GetBasicAttackActor()->End_DoAttack();
}