#include "Character/ActorComponents/CStatusComponent.h"
#include "Global.h"


UCStatusComponent::UCStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(StatusDataTable))
	{
		TArray<FStatusDataTable*> StatusDatas;
		StatusDataTable->GetAllRows<FStatusDataTable>(TEXT("GetAllRows"), StatusDatas);
		for (auto data : StatusDatas)
		{
			if (data->PlayerClass == PlayerClass)
			{
				StatusData = *data;
				break;
			}
		}
	}
	else
		CLog::Print("StatusDataTable Load Failure");
}

void UCStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

