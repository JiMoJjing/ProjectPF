#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBasicAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTPF_API UCBasicAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBasicAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE UCDT_BasicAttack* GetBasicAttackDataTable() { return BasicAttackDataTable; }

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCDT_BasicAttack* BasicAttackDataTable;

public:
	void DoAttack();

private:
	class ACPlayableCharacterBase* OwnerCharacter;
	class UCStateComponent* StateComponent;
};
