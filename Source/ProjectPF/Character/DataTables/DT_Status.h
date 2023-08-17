#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DT_Status.generated.h"

UENUM(BlueprintType)
enum class EPlayableCharacterClass : uint8
{
	Warrior UMETA(DisplayName = "Warrior"),
	Mage UMETA(DisplayName = "Mage"),
	Gunner UMETA(DisplayName = "Gunner")
};

USTRUCT(BlueprintType)
struct FStatusDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPlayableCharacterClass PlayerClass;

	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HpMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HpMaxPerLv;

	// MP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MpMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MpMaxPerLv;

	//Attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackPerLv;

	//Defense
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefensePerLv;

	//Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunSpeed;
};

UCLASS()
class PROJECTPF_API UDT_Status : public UDataTable
{
	GENERATED_BODY()
	
};
