// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_WaitFinish.h"

void UBT_Service_WaitFinish::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
    }
}
