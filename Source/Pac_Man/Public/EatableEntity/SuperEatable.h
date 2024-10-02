// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EatableBase.h"
#include "SuperEatable.generated.h"

UCLASS()
class PAC_MAN_API ASuperEatable : public AEatableBase
{
	GENERATED_BODY()

public:
	ASuperEatable();
	
public:
	virtual float OnEatBegin() override;
	UFUNCTION(BlueprintImplementableEvent)
	void NotifyGhostFear();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnFearGhosts(){};

	// TArray<Ghost>

};
