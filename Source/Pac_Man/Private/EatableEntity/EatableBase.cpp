#include "Pac_Man/Public/EatableEntity/EatableBase.h"

#include "Pac_Man/Pac_ManGameMode.h"


AEatableBase::AEatableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);

	EatableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EatableVisual"));
	EatableMesh->SetupAttachment(RootComponent);

	ScoreGiven = FMath::RandRange(50, 125);
}

float AEatableBase::OnEatBegin()
{
	return GetScoreGiven();
}

void AEatableBase::BeginPlay()
{
	Super::BeginPlay();
	//add to instance count
	if (APac_ManGameMode* GameMode = Cast<APac_ManGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->AddEatableInstance();
	}
	OnDestroyed.AddUniqueDynamic(this, &AEatableBase::OnEatableDestroy);
}

void AEatableBase::OnEatableDestroy(AActor* DestroyedActor)
{
	//remove to instance count
	if (APac_ManGameMode* GameMode = Cast<APac_ManGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RemoveEatableInstance();
	}
}
