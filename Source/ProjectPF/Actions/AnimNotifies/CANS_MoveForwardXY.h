#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CANS_MoveForwardXY.generated.h"

UCLASS()
class PROJECTPF_API UCANS_MoveForwardXY : public UAnimNotifyState
{
	GENERATED_BODY()
	

public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);

private:
	class ACPlayableCharacterBase* OwnerCharacter;
};
