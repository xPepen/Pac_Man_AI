// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GhostCharacterBase.generated.h"

UENUM(BlueprintType)
enum class EGhostState : uint8
{
	Alive UMETA(DisplayName = "Alive"),
	Fear UMETA(DisplayName = "Fear"),
	Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class PAC_MAN_API AGhostCharacterBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponInfo, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> GhostVisual;

public:
	AGhostCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetFearMode();

	UFUNCTION(BlueprintCallable)
	virtual void SetDeadMode();

	UFUNCTION(BlueprintCallable)
	virtual void SetAliveMode();

	UFUNCTION(BlueprintCallable)
	EGhostState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable)
	float GetScoreGiven() const { return ScoreGiven; }

	UFUNCTION(BlueprintCallable)
	FVector GetStartPosition() const { return StartLocation; }

	UFUNCTION(BlueprintCallable)
	void TeleportGhostToHome() { SetActorLocation(StartLocation); };

protected:
	//Those three function mostly use for changing visual

	UFUNCTION(BlueprintImplementableEvent)
	void SetFearMode_BP();

	UFUNCTION(BlueprintImplementableEvent)
	void SetDeadMode_BP();

	UFUNCTION(BlueprintImplementableEvent)
	void SetAliveMode_BP();

protected:
	UFUNCTION()
	void OnHitSomething(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFearModeFinish();

private:
	EGhostState CurrentState;
	FTimerHandle FearModeTimerHandle;

	//Wanted duration for the project :: do not change it
	UPROPERTY(EditAnywhere)
	float FearDuration = 10.0F;

	float ScoreGiven;

	UPROPERTY()
	FVector StartLocation;
};
