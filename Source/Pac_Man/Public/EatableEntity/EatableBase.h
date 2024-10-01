// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EatableBase.generated.h"

UCLASS()
class PAC_MAN_API AEatableBase : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponInfo, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

public:
	AEatableBase();

public:
	float GetScoreGiven() const { return ScoreGiven; }

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnEatableDestroy( AActor* DestroyedActor);

private:
	UPROPERTY(EditAnywhere)
	float ScoreGiven;
};
