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
	virtual void LeftMouseClick();

	/** RunAction 입력 액션시 호출 */
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
	// 현재 움직이고 있는지의 bool 변수
	bool bMoving = false;
	// 현재 Move가 가능한지 불가능한지 설정하는 bool 변수
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
