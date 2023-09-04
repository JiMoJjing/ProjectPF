#pragma once

#include "CoreMinimal.h"
#include "Character/CPlayableCharacterBase.h"
#include "CWarrior.generated.h"


UCLASS()
class PROJECTPF_API ACWarrior : public ACPlayableCharacterBase
{
	GENERATED_BODY()
/**
@@@@ Function @@@@
virtual void Jump() override;
virtual void StopJumping() override;

virtual void Move(const FInputActionValue& Value) override;
void MoveStart();
void MoveEnd();

virtual void Look(const FInputActionValue& Value) override;

virtual void LeftMouseClick();

void RunActionPressed();
void RunActionReleased();

FMoveEvent MoveEvent;
FRunActionPressed OnRunActionPressed;
FRunActionReleased OnRunActionReleased;

@@@@ Actor Component @@@@
State
Level
Status
Hp Mp Offense Defense Speed

@@@@ DataAsset @@@@
CharacterBaseDataAsset
*/



};
