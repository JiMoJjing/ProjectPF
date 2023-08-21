
#include "Character/ActorComponents/Status/CMpComponent.h"
#include "Character/CPlayableCharacterBase.h"

#include "Character/ActorComponents/CStatusComponent.h"
#include "Character/ActorComponents/CLevelComponent.h"
#include "Global.h"

UCMpComponent::UCMpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCMpComponent::BeginPlay()
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

			SetBaseMpMax(data.MpMax);
			SetMpMaxPerLv(data.MpMaxPerLv);
		}
	}
	// LevelComponent
	{
		UCLevelComponent* LevelComponent = CHelpers::GetComponent<UCLevelComponent>(OwnerCharacter);
		if (LevelComponent)
		{
			LevelComponent->OnLevelUp.AddDynamic(this, &UCMpComponent::SetLevel);
			Level = LevelComponent->GetLevel();
		}
	}

	// √ ±‚»≠
	SetFinalMpMax();
	NowMp = FinalMpMax;
}

void UCMpComponent::SetLevel(int32 inLevel)
{
	Level = inLevel;
	SetFinalMpMax();
}

void UCMpComponent::SetAddedMpMax()
{

}

void UCMpComponent::SetFinalMpMax()
{
	FinalMpMax = BaseMpMax;
	FinalMpMax += MpMaxPerLv * Level;
	FinalMpMax += AddedMpMax;
}

void UCMpComponent::SetNowMp(float InFloat)
{

}



void UCMpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString n = "MpMax : ";
	n += FString::SanitizeFloat((double)FinalMpMax);
	CLog::Print(n, 4, 0.001f, FColor::Green);
}