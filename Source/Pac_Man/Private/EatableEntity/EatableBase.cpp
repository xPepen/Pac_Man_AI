#include "Pac_Man/Public/EatableEntity/EatableBase.h"

#include "Pac_Man/Pac_ManGameMode.h"


AEatableBase::AEatableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EatableVisual"));
	WeaponMesh->SetupAttachment(RootComponent);

	ScoreGiven = FMath::RandRange(50, 125);
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
