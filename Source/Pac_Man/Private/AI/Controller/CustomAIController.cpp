#include "Pac_Man/Public/AI/Controller/CustomAIController.h"

ACustomAIController::ACustomAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
