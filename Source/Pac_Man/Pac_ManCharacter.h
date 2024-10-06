// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Public/Component/PacManDataComponent.h"
#include "Components/SphereComponent.h"
#include "Pac_ManCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APac_ManCharacter : public ACharacter
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UPacManDataComponent* DataComponent;

public:
	APac_ManCharacter();

public:
	FORCEINLINE UPacManDataComponent* GetDataComponent() const { return DataComponent; }

protected:
	

	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void SetActorActive(const bool bIsActive);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameOver();

private:
	//Function bind on some event
	UPROPERTY()
	APlayerController* PacManController;

	UFUNCTION()
	void OnRespawnPacMan();

	UFUNCTION()
	void OnHitSomething(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPacManEaten(const int LifeRemain);

	UPROPERTY()
	FVector InitialPosition;

	FTimerHandle RespawnPacmanTimerHandle;

};
