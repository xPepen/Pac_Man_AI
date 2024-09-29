// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pac_ManGameMode.h"
#include "Pac_ManCharacter.h"
#include "UObject/ConstructorHelpers.h"

APac_ManGameMode::APac_ManGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
