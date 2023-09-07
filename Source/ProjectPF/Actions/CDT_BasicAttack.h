#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CDT_BasicAttack.generated.h"

USTRUCT(BlueprintType)
struct FBasicAttackData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
        class UAnimMontage* AnimMontage;

    UPROPERTY(EditAnywhere)
        float PlayRatio = 1.0f;

    UPROPERTY(EditAnywhere)
        FName StartSection;

    UPROPERTY(EditAnywhere)
        bool bCanMove = true;

    UPROPERTY(EditAnywhere)
        bool bPawnControl = true;

};

UCLASS()
class PROJECTPF_API UCDT_BasicAttack : public UDataAsset
{
	GENERATED_BODY()

public:
    FORCEINLINE class ACBasicAttack* GetBasicAttackActor() { return BasicAttackActor; }

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACBasicAttack> BasicAttackClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TArray<FBasicAttackData> BasicAttackDatas;
public:
    void BeginPlay(class ACharacter* InOwnerCharacter);

private:
    class ACBasicAttack* BasicAttackActor;
};
