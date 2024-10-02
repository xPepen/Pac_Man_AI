// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pac_ManCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AI/Character/GhostCharacterBase.h"
#include "Public/EatableEntity/EatableBase.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


APac_ManCharacter::APac_ManCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 0.f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 0.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 0.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	DataComponent = CreateDefaultSubobject<UPacManDataComponent>("Pac_man_DataComponent");

	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &APac_ManCharacter::OnHitSomething);

	GetDataComponent()->OnLifeRemainChanged_Event.AddUniqueDynamic(this, &APac_ManCharacter::OnPacManEaten);
}

void APac_ManCharacter::OnHitSomething(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (AEatableBase* Eatable = Cast<AEatableBase>(OtherActor))
	{
		DataComponent->AddScore(Eatable->OnEatBegin());
		Eatable->Destroy();
	}

	if (AGhostCharacterBase* GhostEntity = Cast<AGhostCharacterBase>(OtherActor))
	{
		if (GhostEntity->GetCurrentState() == EGhostState::Fear)
		{
			DataComponent->AddScore(GhostEntity->GetScoreGiven());
			GhostEntity->SetDeadMode();
		}
	}
}

void APac_ManCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	PacManController = Cast<APlayerController>(NewController);
}

void APac_ManCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitialPosition = GetActorLocation();
}

void APac_ManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &APac_ManCharacter::Move);
	}
}

void APac_ManCharacter::SetActorActive(const bool bIsActive)
{
	this->SetActorTickEnabled(bIsActive);
	this->SetActorHiddenInGame(!bIsActive);
	this->SetActorEnableCollision(bIsActive);
}

void APac_ManCharacter::OnRespawnPacMan()
{
	SetActorActive(true);
	UnPossessed();
}

void APac_ManCharacter::OnPacManEaten(const int LifeRemain)
{
	if (LifeRemain <= 0)
	{
		OnGameOver();
		return;
	}

	SetActorActive(false);
	SetActorLocation(InitialPosition);
	UnPossessed();
	GetWorld()->GetTimerManager().SetTimer(RespawnPacmanTimerHandle, this, &APac_ManCharacter::OnRespawnPacMan, 1.0f,
	                                       false);
}


FVector2d Direction(0, 0);

void APac_ManCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D TargetDirection = Value.Get<FVector2D>();
	if (IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		bool bHasChange = false;

		if (FMath::Abs(TargetDirection.X) > 0.0f && FMath::Abs(TargetDirection.Y) > 0.0f)
		{
			bHasChange = true;
		}

		if (FMath::Abs(TargetDirection.X) > 0.0f && !bHasChange)
		{
			Direction = FVector2D(TargetDirection.X, 0.0f);
		}
		else if (FMath::Abs(TargetDirection.Y) > 0.0f && !bHasChange)
		{
			Direction = FVector2D(0.0f, TargetDirection.Y);
		}
		if(TargetDirection == FVector2D::ZeroVector)
		{
			Direction = FVector2D(0, 0);
		}

		AddMovementInput(ForwardDirection, Direction.Y);
		AddMovementInput(RightDirection, Direction.X);
	}
}
