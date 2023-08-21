
#include "Character/ActorComponents/CLevelComponent.h"
#include "Global.h"


UCLevelComponent::UCLevelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCLevelComponent::BeginPlay()
{
	Super::BeginPlay();
	GetExpData();
}


void UCLevelComponent::AddExp(int32 inExp)
{
	Exp += inExp;
	CheckExp();
	BroadCastOnExpDatas();
}

void UCLevelComponent::CheckExp()
{
	if (Exp >= ExpToLevelUp)
	{
		CLog::Print("LevelUp!", -10, 3.f, FColor::Cyan);
		Level += 1;
		Exp -= ExpToLevelUp;
		GetExpData();
		BroadCastOnLevelUp();
	}
}

void UCLevelComponent::GetExpData()
{
	if (IsValid(ExpDataTable))
	{
		TArray<FExpRequired*> ExpDatas;
		ExpDataTable->GetAllRows<FExpRequired>(TEXT("GetAllRows"), ExpDatas);
		for (auto data : ExpDatas)
		{
			if (Level == data->Level)
				ExpToLevelUp = data->Exp;
		}
	}
}

void UCLevelComponent::BroadCastOnLevelUp()
{
	if (OnLevelUp.IsBound())
		OnLevelUp.Broadcast(Level);
}

void UCLevelComponent::BroadCastOnExpDatas()
{
	if (OnExpUp.IsBound())
		OnExpUp.Broadcast(Exp, ExpToLevelUp);
}

// Called every frame
void UCLevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString n = "Level : ";
	n += FString::FromInt(Level);
	CLog::Print(n, 1, 0.001f, FColor::Green);

	FString exp = "Exp : ";
	exp += FString::FromInt(Exp);
	exp += " (";
	exp += FString::FromInt(ExpToLevelUp);
	exp += ")";
	CLog::Print(exp, 2, 0.001f, FColor::Green);
}

