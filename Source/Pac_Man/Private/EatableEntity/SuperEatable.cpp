#include "Pac_Man/Public/EatableEntity/SuperEatable.h"
#include "Pac_Man/Pac_ManGameMode.h"


ASuperEatable::ASuperEatable()
{
	PrimaryActorTick.bCanEverTick = true;
}

float ASuperEatable::OnEatBegin()
{
	const float Score = Super::OnEatBegin();
	if (const APac_ManGameMode* GameMode = Cast<APac_ManGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->FearAllGhost();
	}

	return Score;
}
