
#include "Character/ActorComponents/CLevelComponent.h"
#include "Global.h"

UCLevelComponent::UCLevelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCLevelComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UCLevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString n = "Level : ";
	n += FString::FromInt(Level);
	CLog::Print(n, 9, 0.001f, FColor::Green);
}

