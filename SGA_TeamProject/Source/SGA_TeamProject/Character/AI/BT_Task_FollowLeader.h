// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Task_FollowLeader.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UBT_Task_FollowLeader : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBT_Task_FollowLeader();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}

	
};
