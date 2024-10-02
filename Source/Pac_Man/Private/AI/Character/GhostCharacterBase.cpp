#include "AI/Character/GhostCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Pac_Man/Pac_ManCharacter.h"


AGhostCharacterBase::AGhostCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsDead = false;

	CurrentState = EGhostState::Alive;
	GetCapsuleComponent()->SetCapsuleHalfHeight(60.0F);
	GhostVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostVisual"));
	GhostVisual->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGhostCharacterBase::OnHitSomething);
	GhostVisual->SetupAttachment(GetCapsuleComponent());
}

void AGhostCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGhostCharacterBase::SetFearMode()
{
	CurrentState = EGhostState::Fear;
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
	if (CurrentState == EGhostState::Fear)return;

	if (const APac_ManCharacter* PacManEntity = Cast<APac_ManCharacter>(OtherActor))
	{
		PacManEntity->GetDataComponent()->RemoveLife();
	}
}
