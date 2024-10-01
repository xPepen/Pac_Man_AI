#include "Pac_Man/Public/Component/PacManDataComponent.h"


UPacManDataComponent::UPacManDataComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Score = 0.0F;
	LifeRemain = 3.F;
}


void UPacManDataComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPacManDataComponent::AddScore(const float InScore)
{
	Score += InScore;
	OnScoreChanged_Event.Broadcast(Score);
}

void UPacManDataComponent::AddLife()
{
	LifeRemain++;
	OnLifeRemainChanged_Event.Broadcast(LifeRemain);
}

void UPacManDataComponent::RemoveLife()
{
	LifeRemain--;
	OnLifeRemainChanged_Event.Broadcast(LifeRemain);
}
