#include "Pac_Man/Public/AI/Controller/CustomAIController.h"

#include "AI/Character/GhostCharacterBase.h"
#include "Pac_Man/Pac_ManGameMode.h"

ACustomAIController::ACustomAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();

	if (APac_ManGameMode* GameMode = Cast<APac_ManGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnGameStateChanged_Event.AddUniqueDynamic(this, &ACustomAIController::OnGameStateChange);
	}
}

void ACustomAIController::OnGameStateChange(const bool State)
{
	if (BehaviorTree)
	{
		if (State)
		{
			RunBehaviorTree(BehaviorTree);
		}
		else
		{
			CleanupBrainComponent();
			if (AGhostCharacterBase* Ghost = Cast<AGhostCharacterBase>(GetPawn()))
			{
				Ghost->TeleportGhostToHome();
				StopMovement();
			}
		}
	}
}
