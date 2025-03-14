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

	//��Ʈ�ѷ��� ���� ���ǵɶ��� �����ɶ� ȣ��Ǵ� �Լ�.
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
