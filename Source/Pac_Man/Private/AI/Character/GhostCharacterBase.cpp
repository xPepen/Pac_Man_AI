#include "AI/Character/GhostCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Pac_Man/Pac_ManCharacter.h"
#include "Pac_Man/Pac_ManGameMode.h"


AGhostCharacterBase::AGhostCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentState = EGhostState::Alive;
	GetCapsuleComponent()->SetCapsuleHalfHeight(60.0F);
	GhostVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostVisual"));
	GhostVisual->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGhostCharacterBase::OnHitSomething);
	GhostVisual->SetupAttachment(GetCapsuleComponent());

	ScoreGiven = FMath::RandRange(100, 200);
}

void AGhostCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (APac_ManGameMode* GameMode = Cast<APac_ManGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnFearGhost_Event.AddUniqueDynamic(this, &AGhostCharacterBase::SetFearMode);
	}

	StartLocation = GetActorLocation();
}

void AGhostCharacterBase::SetFearMode()
{
	CurrentState = EGhostState::Fear;
	if (FearModeTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FearModeTimerHandle);
	}
	GetWorldTimerManager().SetTimer(FearModeTimerHandle, this, &AGhostCharacterBase::OnFearModeFinish, FearDuration,
	                                false);
	SetFearMode_BP();
}

void AGhostCharacterBase::SetDeadMode()
{
	CurrentState = EGhostState::Dead;
	SetDeadMode_BP();
}

void AGhostCharacterBase::SetAliveMode()
{
	CurrentState = EGhostState::Alive;
	SetAliveMode_BP();
}

void AGhostCharacterBase::OnHitSomething(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (CurrentState == EGhostState::Fear || CurrentState == EGhostState::Dead)return;

	if (const APac_ManCharacter* PacManEntity = Cast<APac_ManCharacter>(OtherActor))
	{
		PacManEntity->GetDataComponent()->RemoveLife();
	}
}

void AGhostCharacterBase::OnFearModeFinish()
{
	//check if we are not eat by pac man
	if (CurrentState == EGhostState::Fear)
	{
		SetAliveMode();
	}
	//else we are dead and we dont need to handle it here
}
