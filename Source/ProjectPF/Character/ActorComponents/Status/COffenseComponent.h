#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COffenseComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTPF_API UCOffenseComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter �Լ��� �������Ʈ���� ����� �͵� ���ο��ξ���. */
	UFUNCTION(BlueprintPure, Category = "Offense")
		FORCEINLINE float GetBaseOffense() { return BaseOffense; }

	UFUNCTION(BlueprintPure, Category = "Offense")
		FORCEINLINE float GetAddedOffense() { return AddedOffense; }

	UFUNCTION(BlueprintPure, Category = "Offense")
		FORCEINLINE float GetFinalOffense() { return FinalOffense; }

private:
	//�÷��̾��� �⺻ Offense
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float BaseOffense;
	// Lv�� ��� Offense
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float OffensePerLv;
	//��� ������ ���� Offense ��·� ����
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float AddedOffense = 0.f;
	//Base + Added ���� ���� Offense ����
	UPROPERTY(VisibleAnywhere, Category = "Offense")
		float FinalOffense;

	//���� Level
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
