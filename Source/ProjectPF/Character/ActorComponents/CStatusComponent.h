#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/DataTables/DT_Status.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	// Data 
	UPROPERTY(EditDefaultsOnly)
		FStatusDataTable StatusData;

public:
	UFUNCTION(BlueprintPure)
		FStatusDataTable GetStatusData() const { return StatusData; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* StatusDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "StatusDataTable != nullptr", EditConditionHides))
		EPlayableCharacterClass PlayerClass;
};
