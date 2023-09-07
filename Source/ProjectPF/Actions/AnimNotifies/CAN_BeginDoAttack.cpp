#include "Actions/AnimNotifies/CAN_BeginDoAttack.h"

#include "Character/ActorComponents/CBasicAttackComponent.h"
#include "Actions/CBasicAttack.h"
#include "Actions/CDT_BasicAttack.h"


FString UCAN_BeginDoAttack::GetNotifyName_Implementation() const
{
	return "BeginAttack";
}

void UCAN_BeginDoAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	if (MeshComp == nullptr)
		return;
	if (MeshComp->GetOwner() == nullptr)
		return;

	UCBasicAttackComponent* component = Cast<UCBasicAttackComponent>(MeshComp->GetOwner()->GetComponentByClass(UCBasicAttackComponent::StaticClass()));
	if (component == nullptr)
		return;

	component->GetBasicAttackDataTable()->GetBasicAttackActor()->Begin_DoAttack();
}