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
		CLog::Print("StatusDataTable Load Success");

		TArray<FStatusDataTableStruct*> StatusDatas;
		StatusDataTable->GetAllRows<FStatusDataTableStruct>(TEXT("GetAllRows"), StatusDatas);
		for (auto data : StatusDatas)
		{
			if (data->PlayerClass == PlayerClass)
			{
				StatusData = *data;
				CLog::Print(StatusData.Attack);
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

