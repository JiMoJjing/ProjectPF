#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSpeedComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCSpeedComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Getter �Լ��� �������Ʈ���� ����� �͵� ���ο��ξ���. */
	UFUNCTION(BlueprintPure, Category = "WalkSpeed")
		FORCEINLINE float GetBaseWalkSpeed() { return BaseWalkSpeed; }

	UFUNCTION(BlueprintPure, Category = "WalkSpeed")
		FORCEINLINE float GetAddedWalkSpeed() { return AddedWalkSpeed; }

	UFUNCTION(BlueprintPure, Category = "WalkSpeed")
		FORCEINLINE float GetFinalWalkSpeed() { return FinalWalkSpeed; }

	UFUNCTION(BlueprintPure, Category = "RunSpeed")
		FORCEINLINE float GetBaseRunSpeed() { return BaseRunSpeed; }

	UFUNCTION(BlueprintPure, Category = "RunSpeed")
		FORCEINLINE float GetAddedRunSpeed() { return AddedRunSpeed; }

	UFUNCTION(BlueprintPure, Category = "RunSpeed")
		FORCEINLINE float GetFinalRunSpeed() { return FinalRunSpeed; }


private:
	//�÷��̾��� �⺻ WalkSpeed
	UPROPERTY(VisibleAnywhere, Category = "WalkSpeed")
		float BaseWalkSpeed;
	//��� ������ ���� WalkSpeed ��·� ����
	UPROPERTY(VisibleAnywhere, Category = "WalkSpeed")
		float AddedWalkSpeed = 0.f;
	//Base + Added ���� ���� WalkSpeed ����
	UPROPERTY(VisibleAnywhere, Category = "WalkSpeed")
		float FinalWalkSpeed;

	//�÷��̾��� �⺻ RunSpeed
	UPROPERTY(VisibleAnywhere, Category = "RunSpeed")
		float BaseRunSpeed;
	//��� ������ ���� RunSpeed ��·� ����
	UPROPERTY(VisibleAnywhere, Category = "RunSpeed")
		float AddedRunSpeed = 0.f;
	//Base + Added ���� ���� RunSpeed ����
	UPROPERTY(VisibleAnywhere, Category = "RunSpeed")
		float FinalRunSpeed;

public:
	UFUNCTION(BlueprintCallable, Category = "WalkSpeed")
		void SetBaseWalkSpeed(float InWalkSpeed) { BaseWalkSpeed = InWalkSpeed; }

	UFUNCTION(BlueprintCallable, Category = "WalkSpeed")
		void SetAddedWalkSpeed();

	UFUNCTION(BlueprintCallable, Category = "WalkSpeed")
		void SetFinalWalkSpeed();

	UFUNCTION(BlueprintCallable, Category = "RunSpeed")
		void SetBaseRunSpeed(float InRunSpeed) { BaseRunSpeed = InRunSpeed; }

	UFUNCTION(BlueprintCallable, Category = "RunSpeed")
		void SetAddedRunSpeed();

	UFUNCTION(BlueprintCallable, Category = "RunSpeed")
		void SetFinalRunSpeed();

	/** DELEGATE �� �Լ� */
	UFUNCTION(BlueprintCallable)
		void BindRunActionPressed();
	UFUNCTION(BlueprintCallable)
		void BindRunActionReleased();

private:
	class ACPlayableCharacterBase* OwnerCharacter;


public:	
	UCSpeedComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
