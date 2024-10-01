#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PacManDataComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeRemainChangedSignature, int, LifeRemain);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedSignature, float, NewScore);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PAC_MAN_API UPacManDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPacManDataComponent();

public:
	UPROPERTY(BlueprintAssignable)
	FOnLifeRemainChangedSignature OnLifeRemainChanged_Event;

	UPROPERTY(BlueprintAssignable)
	FOnScoreChangedSignature OnScoreChanged_Event;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	float GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable)
	int GetLifeRemain() const { return LifeRemain; }

	UFUNCTION(BlueprintCallable)
	void AddScore(const float InScore);
	
	UFUNCTION(BlueprintCallable)
	void AddLife();
	
	UFUNCTION(BlueprintCallable)
	void RemoveLife();

private:
	float Score;
	UPROPERTY(EditAnywhere)
	float LifeRemain;
};
