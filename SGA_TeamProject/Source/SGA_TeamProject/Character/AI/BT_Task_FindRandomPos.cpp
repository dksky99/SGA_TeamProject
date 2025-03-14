// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_FindRandomPos.h"
#include "../../Controller/CAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBT_Task_FindRandomPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//���� ���ǵ� Pawn ã��
	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();

	//���� ��ȯ
	if (currentPawn->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;



	FVector pos = currentPawn->GetActorLocation();

	//NavMesh ã��
	auto naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (naviSystem->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	//��ȯ���� ������ ��ġ.
	FNavLocation randLocation;
	//���� �ݰ���� ������ ������ �������� �Լ�
	if (naviSystem->GetRandomPointInNavigableRadius(pos, 500.0f, randLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandPos")), randLocation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
