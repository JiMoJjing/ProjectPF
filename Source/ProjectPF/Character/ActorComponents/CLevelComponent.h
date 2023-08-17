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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCLevelComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		int32 Level = 1;
	UPROPERTY()
		int32 Exp = 0;

	UPROPERTY(EditAnywhere)
		class UDataTable* ExpDataTable;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE int32 GetLevel() { return Level; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE int32 GetExp() { return Exp; }


public:	
	UCLevelComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
