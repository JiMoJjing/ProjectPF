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

protected:
	/** CStateComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents")
		class UCStateComponent* StateComponent;

protected:
	/** DataAsset */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAssets")
		class UCDA_CharacterBase* CharacterBaseDataAsset;


public:
	ACPlayableCharacterBase();	

protected:

	/** Jump �Է� �׼ǽ� ȣ�� */
	virtual void Jump() override;
	virtual void StopJumping() override;

	/** Move �Է� �׼ǽ� ȣ�� */
	virtual void Move(const FInputActionValue& Value) override;

	/** Look �Է� �׼ǽ� ȣ�� */
	virtual void Look(const FInputActionValue& Value) override;

	/** LeftMouseClick �Է� �׼ǽ� ȣ�� */
	virtual void LeftMouseClick() override;

	/** LeftShift �Է� �׼ǽ� ȣ�� */
	void LeftShiftPressed();
	void LeftShiftReleased();

	/** State�� ��������Ʈ�� ���ε� �� �Լ� */
	virtual void OnStateChanged_Implementation(EPlayableCharacterState InPrevState, EPlayableCharacterState InNewState) override;

	/** State�� Walking�� �Ǹ� ��������Ʈ�� ���� �� �Լ� */
	virtual void SetWalkingMode() override;

	/** State�� Running�� �Ǹ� ��������Ʈ�� ���� �� �Լ� */
	virtual void SetRunningMode() override;

	virtual void Test_Implementation() override;

	UFUNCTION(BlueprintCallable)
		void ChangeBindingAction(class UInputAction* InAction, FKey InKey);

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	
public:
	void Jump2(FKey PressedKey);
};
