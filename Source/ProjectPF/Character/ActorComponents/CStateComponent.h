#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EPlayableCharacterState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Running"),
	Jumping UMETA(DisplayName = "Jumping"),
	Attacking = 10 UMETA(DisplayName = "Attacking"),
	Casting UMETA(DisplayName = "Casting")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayableCharacterStateChanged, EPlayableCharacterState, InPrevState, EPlayableCharacterState, InNewState);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE EPlayableCharacterState GetState() { return State; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsState(EPlayableCharacterState InState) { return State == InState; }

	UFUNCTION(BlueprintCallable)
		void SetState(EPlayableCharacterState InState);

public:
	UPROPERTY(BlueprintAssignable)
		FPlayableCharacterStateChanged OnStateChanged;

private:
	EPlayableCharacterState State = EPlayableCharacterState::Idle;

	class ACPlayableCharacterBase* OwnerCharacter;
public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
