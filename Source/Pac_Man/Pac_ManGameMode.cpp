// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pac_ManGameMode.h"
#include "Pac_ManCharacter.h"
#include "UObject/ConstructorHelpers.h"

APac_ManGameMode::APac_ManGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APac_ManGameMode::RemoveEatableInstance()
{
	EatableInstance--;

	//this mean the game is finish
	if (EatableInstance <= 0)
	{
		OnEatableReachZero_Event.Broadcast();
	}
}

void APac_ManGameMode::SetIsGamePlaying(const bool NewState)
{
	IsPlaying = NewState;
	if(OnGameStateChanged_Event.IsBound())
	{
		OnGameStateChanged_Event.Broadcast(IsPlaying);
	}
}
