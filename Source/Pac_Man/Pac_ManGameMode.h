#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pac_ManGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEatableReachZeroSignature);

UCLASS(minimalapi)
class APac_ManGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APac_ManGameMode();
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnEatableReachZeroSignature OnEatableReachZero_Event;

public:
	void AddEatableInstance(){EatableInstance++;};
	void RemoveEatableInstance();

private:
	int EatableInstance;
};
