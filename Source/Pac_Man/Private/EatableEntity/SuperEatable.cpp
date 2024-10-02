// Fill out your copyright notice in the Description page of Project Settings.


#include "Pac_Man/Public/EatableEntity/SuperEatable.h"


// Sets default values
ASuperEatable::ASuperEatable()
{
	PrimaryActorTick.bCanEverTick = true;
}

float ASuperEatable::OnEatBegin()
{
	const float Score = Super::OnEatBegin();
	NotifyGhostFear();
	return Score;
}

void ASuperEatable::BeginPlay()
{
	Super::BeginPlay();
}
