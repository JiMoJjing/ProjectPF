#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDefenseComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTPF_API UCDefenseComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	/** Getter �Լ��� �������Ʈ���� ����� �͵� ���ο��ξ���. */
	UFUNCTION(BlueprintPure, Category = "Defense")
		FORCEINLINE float GetBaseDefense() { return BaseDefense; }

	UFUNCTION(BlueprintPure, Category = "Defense")
		FORCEINLINE float GetAddedDefense() { return AddedDefense; }

	UFUNCTION(BlueprintPure, Category = "Defense")
		FORCEINLINE float GetFinalDefense() { return FinalDefense; }

private:
	//�÷��̾��� �⺻ Defense
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float BaseDefense;
	// Lv�� ��� Defense
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float DefensePerLv;
	//��� ������ ���� Defense ��·� ����
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float AddedDefense = 0.f;
	//Base + Added ���� ���� Defense ����
	UPROPERTY(VisibleAnywhere, Category = "Defense")
		float FinalDefense;

	//���� Level
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