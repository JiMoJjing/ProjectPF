
#include "Character/ActorComponents/Status/CHpComponent.h"
#include "Character/CPlayableCharacterBase.h"

#include "Character/ActorComponents/CStatusComponent.h"
#include "Global.h"

UCHpComponent::UCHpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCHpComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACPlayableCharacterBase>(GetOwner());
	//UCStatusComponent* StatusComponent = OwnerCharacter->FindComponentByClass<UCStatusComponent>();
	//UCStatusComponent* StatusComponent = Cast<UCStatusComponent>(OwnerCharacter->GetComponentByClass(UCStatusComponent::StaticClass()));
	UCStatusComponent* StatusComponent = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	if (StatusComponent)
	{
		FStatusDataTable data;
		data = StatusComponent->GetStatusData();

		SetBaseHpMax(data.HpMax);
		SetHpMaxPerLv(data.HpMaxPerLv);
	}
}



void UCHpComponent::SetBaseHpMax(float InHpMax)
{
	BaseHpMax = InHpMax;
	SetFinalHpMax();
}

void UCHpComponent::SetHpMaxPerLv(float InHpMaxPerLv)
{
	HpMaxPerLv = InHpMaxPerLv;
	SetFinalHpMax();
}

void UCHpComponent::SetAddedHpMax()
{

}

void UCHpComponent::SetFinalHpMax()
{
	FinalHpMax = BaseHpMax;
	FinalHpMax += HpMaxPerLv;
}

void UCHpComponent::SetNowHp(float InFloat)
{
}


void UCHpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString n = "HpMax : ";
	n += FString::SanitizeFloat((double)FinalHpMax);
	CLog::Print(n, 10, 0.001f, FColor::Green);
}



