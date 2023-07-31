#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Character/ICharacter.h"
#include "CPlayableCharacterBase.generated.h"

UCLASS()
class PROJECTPF_API ACPlayableCharacterBase : public ACharacter, public IICharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */ 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/** LeftMouseClick Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LeftMouseClickAction;

	/** LeftShift Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LeftShiftAction;

	/** CStateComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCStateComponent* StateComponent;

	/** DataAsset */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAssets", meta = (AllowPrivateAccess = "true"))
		class UCDA_CharacterBase* CharacterBaseDataAsset;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bMove = false;
protected:
	/** Bind Key Change */
	UFUNCTION(BlueprintCallable)
		void ChangeBindingAction(class UInputAction* InAction, FKey InKey);


public:
	ACPlayableCharacterBase();	

protected:

	/** Jump 입력 액션시 호출 */
	virtual void Jump() override;
	virtual void StopJumping() override;

	/** Move 입력 액션시 호출 */
	virtual void Move(const FInputActionValue& Value) override;

	/** Move 입력 시작시 호출 */
	void MoveStart();
	/** Move 입력 종료시 호출 */
	void MoveEnd();

	/** Look 입력 액션시 호출 */
	virtual void Look(const FInputActionValue& Value) override;

	/** LeftMouseClick 입력 액션시 호출 */
	virtual void LeftMouseClick() override;

	/** LeftShift 입력 액션시 호출 */
	void LeftShiftPressed();
	void LeftShiftReleased();

	/** Move 일 때 Walking 인지 Running 인지 체크해서 SetState(CStateComponent) 할 함수 */
	void OnMoveState();

	/** State가 Walking이 되면 델리게이트로 실행 될 함수 */
	virtual void SetWalkingMode() override;

	/** State가 Running이 되면 델리게이트로 실행 될 함수 */
	virtual void SetRunningMode() override;

	/** State의 델리게이트에 바인딩 할 함수 */
	virtual void OnStateChanged_Implementation(EPlayableCharacterState InPrevState, EPlayableCharacterState InNewState) override;


	virtual void Test_Implementation() override;

private:
	/** WalkingSpeed와 RunningSpeed 인데 Status Component로 이식 할 것 */
	float WalkingSpeed = 200.f;
	float RunningSpeed = 600.f;


protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	

};
