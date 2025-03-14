// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController();

	//컨트롤러가 폰에 빙의될때와 해제될때 호출되는 함수.
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION()
	void RandMove();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlackboardData* _blackBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBehaviorTree* _behaviorTree;

private:
	UPROPERTY()
	FTimerHandle _timerHandle;


	
};
