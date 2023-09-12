#include "Actions/CDT_BasicAttack.h"

#include "GameFramework/Character.h"
#include "Global.h"
#include "Actions/CBasicAttack.h"
#include "Character/CPlayableCharacterBase.h"

void UCDT_BasicAttack::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;

	if (!!BasicAttackClass)
	{
		BasicAttackActor = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACBasicAttack>(BasicAttackClass, transform, InOwnerCharacter);
		BasicAttackActor->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		BasicAttackActor->SetActorLabel(FString("BasicAttackActor"));
		BasicAttackActor->SetDatas(BasicAttackDatas);
		UGameplayStatics::FinishSpawningActor(BasicAttackActor, transform);
	}
}
