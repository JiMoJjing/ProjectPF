#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDefenseComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTPF_API UCDefenseComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter 함수들 블루프린트에서 사용할 것도 염두에두었다. */
	UFUNCTION(BlueprintPure, Category = "Defense")
		FORCEINLINE float GetBaseDefense() { return BaseDefense; }

	UFUNCTION(BlueprintPure, Category = "Defense")
		FORCEINLINE float GetAddedDefense() { return AddedDefense; }

	UFUNCTION(BlueprintPure, Category = "Defense")
		FORCEINLINE float GetFinalDefense() { return FinalDefense; }

private:
	//플레이어의 기본 Defense
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float BaseDefense;
	// Lv당 상승 Defense
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float DefensePerLv;
	//장비나 버프로 인한 Defense 상승량 관리
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float AddedDefense = 0.f;
	//Base + Added 합쳐 최종 Defense 관리
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float FinalDefense;

	//현재 Level
	UPROPERTY(VisibleAnywhere, Category = "Level")
		int32 Level;


public:
	UFUNCTION(BlueprintCallable, Category = "Defense")
		void SetBaseDefense(float InDefense) { BaseDefense = InDefense; }

	UFUNCTION(BlueprintCallable, Category = "Defense")
		void SetDefensePerLv(float InDefensePerLv) { DefensePerLv = InDefensePerLv; }

	UFUNCTION(BlueprintCallable, Category = "Defense")
		void SetAddedDefense();

	UFUNCTION(BlueprintCallable, Category = "Defense")
		void SetFinalDefense();

	UFUNCTION(BlueprintCallable, Category = "Level")
		void SetLevel(int32 inLevel);

private:
	class ACPlayableCharacterBase* OwnerCharacter;

public:
	UCDefenseComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};