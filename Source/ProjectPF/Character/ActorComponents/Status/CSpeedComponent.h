#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSpeedComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCSpeedComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Getter 함수들 블루프린트에서 사용할 것도 염두에두었다. */
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
	//플레이어의 기본 WalkSpeed
	UPROPERTY(EditDefaultsOnly, Category = "WalkSpeed")
		float BaseWalkSpeed;
	//장비나 버프로 인한 WalkSpeed 상승량 관리
	UPROPERTY(EditDefaultsOnly, Category = "WalkSpeed")
		float AddedWalkSpeed = 0.f;
	//Base + Added 합쳐 최종 WalkSpeed 관리
	UPROPERTY(EditDefaultsOnly, Category = "WalkSpeed")
		float FinalWalkSpeed;

	//플레이어의 기본 RunSpeed
	UPROPERTY(EditDefaultsOnly, Category = "RunSpeed")
		float BaseRunSpeed;
	//장비나 버프로 인한 RunSpeed 상승량 관리
	UPROPERTY(EditDefaultsOnly, Category = "RunSpeed")
		float AddedRunSpeed = 0.f;
	//Base + Added 합쳐 최종 RunSpeed 관리
	UPROPERTY(EditDefaultsOnly, Category = "RunSpeed")
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

	/** DELEGATE 용 함수 */
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
