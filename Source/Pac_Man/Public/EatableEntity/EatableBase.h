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
	TObjectPtr<UStaticMeshComponent> EatableMesh;

public:
	AEatableBase();

public:
	virtual float OnEatBegin();

protected:
	virtual void BeginPlay() override;
	float GetScoreGiven() const { return ScoreGiven; }

private:
	UFUNCTION()
	void OnEatableDestroy( AActor* DestroyedActor);

private:
	UPROPERTY(EditAnywhere)
	float ScoreGiven;
};
