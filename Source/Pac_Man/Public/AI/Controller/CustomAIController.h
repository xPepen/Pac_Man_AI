#pragma once

#include "CoreMinimal.h"
#include"AIController.h"
#include "CustomAIController.generated.h"
class UBehaviorTree;

UCLASS()
class PAC_MAN_API ACustomAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACustomAIController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;


private:
	UFUNCTION()
	void OnGameStateChange(const bool State);
};
