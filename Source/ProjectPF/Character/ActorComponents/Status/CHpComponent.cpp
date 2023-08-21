
#include "Character/ActorComponents/Status/CHpComponent.h"
#include "Character/CPlayableCharacterBase.h"

#include "Character/ActorComponents/CStatusComponent.h"
#include "Character/ActorComponents/CLevelComponent.h"
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

	// StatusComponent 
	{
		UCStatusComponent* StatusComponent = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
		if (StatusComponent)
		{
			FStatusDataTable data;
			data = StatusComponent->GetStatusData();

			SetBaseHpMax(data.HpMax);
			SetHpMaxPerLv(data.HpMaxPerLv);
		}
	}
	// LevelComponent
	{
		UCLevelComponent* LevelComponent = CHelpers::GetComponent<UCLevelComponent>(OwnerCharacter);
		if (LevelComponent)
		{
			LevelComponent->OnLevelUp.AddDynamic(this, &UCHpComponent::SetLevel);
			//레벨 초기화
			Level = LevelComponent->GetLevel();
		}
	}

	// 초기화
	SetFinalHpMax();
	NowHp = FinalHpMax;
}

void UCHpComponent::SetLevel(int32 inLevel)
{
	Level = inLevel;
	SetFinalHpMax();
}

void UCHpComponent::SetAddedHpMax()
{

}

void UCHpComponent::SetFinalHpMax()
{
	FinalHpMax = BaseHpMax;
	FinalHpMax += HpMaxPerLv * Level;
	FinalHpMax += AddedHpMax;
}

void UCHpComponent::SetNowHp(float InFloat)
{

}



void UCHpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString n = "HpMax : ";
	n += FString::SanitizeFloat((double)FinalHpMax);
	CLog::Print(n, 3, 0.001f, FColor::Green);
}



