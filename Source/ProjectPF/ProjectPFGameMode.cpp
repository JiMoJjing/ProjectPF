// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectPFGameMode.h"
#include "ProjectPFCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectPFGameMode::AProjectPFGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/ProjectPF/Characters/BP_CPlayableCharacterBase.BP_CPlayableCharacterBase_C'"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
