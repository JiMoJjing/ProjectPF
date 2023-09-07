#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COffenseComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTPF_API UCOffenseComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter 함수들 블루프린트에서 사용할 것도 염두에두었다. */
	UFUNCTION(BlueprintPure, Category = "Offense")
		FORCEINLINE float GetBaseOffense() { return BaseOffense; }

	UFUNCTION(BlueprintPure, Category = "Offense")
		FORCEINLINE float GetAddedOffense() { return AddedOffense; }

	UFUNCTION(BlueprintPure, Category = "Offense")
		FORCEINLINE float GetFinalOffense() { return FinalOffense; }

private:
	//플레이어의 기본 Offense
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float BaseOffense;
	// Lv당 상승 Offense
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float OffensePerLv;
	//장비나 버프로 인한 Offense 상승량 관리
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float AddedOffense = 0.f;
	//Base + Added 합쳐 최종 Offense 관리
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float FinalOffense;

	//현재 Level
	UPROPERTY(VisibleAnywhere, Category = "Level")
		int32 Level;


public:
	UFUNCTION(BlueprintCallable, Category = "Offense")
		void SetBaseOffense(float InOffense) { BaseOffense = InOffense; }

	UFUNCTION(BlueprintCallable, Category = "Offense")
		void SetOffensePerLv(float InOffensePerLv) { OffensePerLv = InOffensePerLv; }

	UFUNCTION(BlueprintCallable, Category = "Offense")
		void SetAddedOffense();

	UFUNCTION(BlueprintCallable, Category = "Offense")
		void SetFinalOffense();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void SetLevel(int32 inLevel);

private:
	class ACPlayableCharacterBase* OwnerCharacter;

public:
	UCOffenseComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
