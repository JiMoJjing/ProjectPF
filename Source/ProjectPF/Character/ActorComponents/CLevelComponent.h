#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CLevelComponent.generated.h"

USTRUCT(BlueprintType)
struct FExpRequired : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// Level and Exp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Exp;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelUp, int32, inLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FExpUp, int32, inExp, int32, inExpToLevelUp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCLevelComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		int32 Level = 1;
	UPROPERTY()
		int32 Exp = 0;
	UPROPERTY()
		int32 ExpToLevelUp = 0;

	UPROPERTY(EditAnywhere)
		class UDataTable* ExpDataTable;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE int32 GetLevel() { return Level; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE int32 GetExp() { return Exp; }

	UFUNCTION(BlueprintCallable)
		void AddExp(int32 inExp);

	UPROPERTY(BlueprintAssignable)
		FLevelUp OnLevelUp;
	UPROPERTY(BlueprintAssignable)
		FExpUp OnExpUp;

private:
	/** Exp���� �� ���� Levelup���� �˻� �� �Լ� */
	void CheckExp();
	/** DataTable���� Level�� �´� exp ã�ƿ��� �Լ� */
	void GetExpData();
	/** LevelUp �ϸ� ��������Ʈ BroadCast �� �Լ� */
	void BroadCastOnLevelUp();
	/** Exp ���� �Ǹ� ��������Ʈ BroadCast �� �Լ� */
	void BroadCastOnExpDatas();
public:	
	UCLevelComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
