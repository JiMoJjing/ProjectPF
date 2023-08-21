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
	/** Exp얻을 때 마다 Levelup인지 검사 할 함수 */
	void CheckExp();
	/** DataTable에서 Level에 맞는 exp 찾아오는 함수 */
	void GetExpData();
	/** LevelUp 하면 델리게이트 BroadCast 할 함수 */
	void BroadCastOnLevelUp();
	/** Exp 변경 되면 델리게이트 BroadCast 할 함수 */
	void BroadCastOnExpDatas();
public:	
	UCLevelComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
