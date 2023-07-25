#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputActionValue.h"
#include "ActorComponents/CStateComponent.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};


class PROJECTPF_API IICharacter
{
	GENERATED_BODY()
public:
	virtual void Move(const FInputActionValue& Value) = 0;
	virtual void Look(const FInputActionValue& Value) = 0;
	virtual void Jump() = 0;
	virtual void StopJumping() = 0;
	
	virtual void LeftMouseClick() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnStateChanged(EPlayableCharacterState InPrevState, EPlayableCharacterState InNewState);

	virtual void SetWalkingMode() = 0;
	virtual void SetRunningMode() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Test();
};
