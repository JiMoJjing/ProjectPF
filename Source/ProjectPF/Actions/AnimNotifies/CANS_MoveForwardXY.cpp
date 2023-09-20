#include "Actions/AnimNotifies/CANS_MoveForwardXY.h"

#include "Character/CPlayableCharacterBase.h"
#include "Character/ActorComponents/Status/CSpeedComponent.h"

FString UCANS_MoveForwardXY::GetNotifyName_Implementation() const
{
	return "MoveForwardXY";
}

void UCANS_MoveForwardXY::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (MeshComp == nullptr)
		return;
	if (MeshComp->GetOwner() == nullptr)
		return;

	OwnerCharacter = Cast<ACPlayableCharacterBase>(MeshComp->GetOwner());

	if (OwnerCharacter == nullptr)
		return;

	UCSpeedComponent* component = Cast<UCSpeedComponent>(OwnerCharacter->GetComponentByClass(UCSpeedComponent::StaticClass()));

	if (component == nullptr)
		return;

	OwnerCharacter->MoveForwardXY(component->GetFinalWalkSpeed());
}
