#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Character/ICharacter.h"
#include "CPlayableCharacterBase.generated.h"

DECLARE_EVENT(ACPlayableCharacterBase, FMoveEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRunActionPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRunActionReleased);

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
		class UInputAction* RunAction;

	/** CStateComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCStateComponent* StateComponent;

	/** CStatusComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCStatusComponent* StatusComponent;

	/** CLevelComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCLevelComponent* LevelComponent;

	/** CHpComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCHpComponent* HpComponent;

	/** CMpComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCMpComponent* MpComponent;

	/** COffenseComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCOffenseComponent* OffenseComponent;

	/** CDefenseComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCDefenseComponent* DefenseComponent;

	/** CSpeedComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCSpeedComponent* SpeedComponent;

	/** CBasicAttackComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCBasicAttackComponent* BasicAttackComponent;

	// CWeaponComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UCWeaponComponent* WeaponComponent;

	/** DataAsset */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAssets", meta = (AllowPrivateAccess = "true"))
		class UCDA_CharacterBase* CharacterBaseDataAsset;

protected:
	/** Bind Key Change */
	UFUNCTION(BlueprintCallable)
		void ChangeBindingAction(class UInputAction* InAction, FKey InKey);
public:
	ACPlayableCharacterBase();	

protected:

	/** Jump �Է� �׼ǽ� ȣ�� */
	virtual void Jump() override;
	virtual void StopJumping() override;

	/** Move �Է� �׼ǽ� ȣ�� */
	virtual void Move(const FInputActionValue& Value) override;

	/** Move �Է� ���۽� ȣ�� */
	void MoveStart();
	/** Move �Է� ����� ȣ�� */
	void MoveEnd();

	/** Look �Է� �׼ǽ� ȣ�� */
	virtual void Look(const FInputActionValue& Value) override;

	/** LeftMouseClick �Է� �׼ǽ� ȣ�� */
	virtual void LeftMouseClick();

	/** RunAction �Է� �׼ǽ� ȣ�� */
	void RunActionPressed();
	void RunActionReleased();


	virtual void Test_Implementation() override;

public:
	// bMoving Getter
	bool GetbMoving() { return bMoving; }

	// bCanMove Getter, Setter
	void SetbCanMove(bool InBool) { bCanMove = InBool; }
	bool GetbCanMove() { return bCanMove; }

	// MoveForward XY
	void MoveForwardXY(float InSpeed);

	void SetCharacterRotationYaw();

private:
	// ���� �����̰� �ִ����� bool ����
	bool bMoving = false;
	// ���� Move�� �������� �Ұ������� �����ϴ� bool ����
	bool bCanMove = true;

/** DECLARE_EVENT */
public:
	FMoveEvent& OnMoveEvent() { return MoveEvent; }
private:
	FMoveEvent MoveEvent;
	
//==================================================

/** DELEGATE */
public:
	UPROPERTY(BlueprintAssignable)
		FRunActionPressed OnRunActionPressed;

	UPROPERTY(BlueprintAssignable)
		FRunActionReleased OnRunActionReleased;


protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	

};
