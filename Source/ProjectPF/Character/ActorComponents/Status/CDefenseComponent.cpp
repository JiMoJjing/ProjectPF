
#include "Character/ActorComponents/Status/CDefenseComponent.h"
#include "Character/CPlayableCharacterBase.h"

#include "Character/ActorComponents/CStatusComponent.h"
#include "Character/ActorComponents/CLevelComponent.h"
#include "Global.h"

UCDefenseComponent::UCDefenseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCDefenseComponent::BeginPlay()
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

			SetBaseDefense(data.Defense);
			SetDefensePerLv(data.DefensePerLv);
		}
	}
	// LevelComponent
	{
		UCLevelComponent* LevelComponent = CHelpers::GetComponent<UCLevelComponent>(OwnerCharacter);
		if (LevelComponent)
		{
			LevelComponent->OnLevelUp.AddDynamic(this, &UCDefenseComponent::SetLevel);
			Level = LevelComponent->GetLevel();
		}
	}

	// √ ±‚»≠
	SetFinalDefense();
}

void UCDefenseComponent::SetLevel(int32 inLevel)
{
	Level = inLevel;
	SetFinalDefense();
}

void UCDefenseComponent::SetAddedDefense()
{

}

void UCDefenseComponent::SetFinalDefense()
{
	FinalDefense = BaseDefense;
	FinalDefense += DefensePerLv * Level;
	FinalDefense += AddedDefense;
}


void UCDefenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString n = "Defense : ";
	n += FString::SanitizeFloat((double)FinalDefense);
	CLog::Print(n, 6, 0.001f, FColor::Green);
}