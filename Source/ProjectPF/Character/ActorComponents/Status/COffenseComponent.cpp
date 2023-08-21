
#include "Character/ActorComponents/Status/COffenseComponent.h"
#include "Character/CPlayableCharacterBase.h"

#include "Character/ActorComponents/CStatusComponent.h"
#include "Character/ActorComponents/CLevelComponent.h"
#include "Global.h"

UCOffenseComponent::UCOffenseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCOffenseComponent::BeginPlay()
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

			SetBaseOffense(data.Offense);
			SetOffensePerLv(data.OffensePerLv);
		}
	}
	// LevelComponent
	{
		UCLevelComponent* LevelComponent = CHelpers::GetComponent<UCLevelComponent>(OwnerCharacter);
		if (LevelComponent)
		{
			LevelComponent->OnLevelUp.AddDynamic(this, &UCOffenseComponent::SetLevel);
			Level = LevelComponent->GetLevel();
		}
	}

	// √ ±‚»≠
	SetFinalOffense();
}

void UCOffenseComponent::SetLevel(int32 inLevel)
{
	Level = inLevel;
	SetFinalOffense();
}

void UCOffenseComponent::SetAddedOffense()
{

}

void UCOffenseComponent::SetFinalOffense()
{
	FinalOffense = BaseOffense;
	FinalOffense += OffensePerLv * Level;
	FinalOffense += AddedOffense;
}


void UCOffenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString n = "Offense : ";
	n += FString::SanitizeFloat((double)FinalOffense);
	CLog::Print(n, 5, 0.001f, FColor::Green);
}
