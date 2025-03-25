// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_MoveToEffectiveRange.h"
#include "../../Controller/CAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../CharacterBase.h"
#include "../../Helper/H_Relation.h"

EBTNodeResult::Type UBT_Task_MoveToEffectiveRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//현재 빙의된 Pawn 찾기
	auto currentPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	AActor* remain = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	//실패 반환
	if (currentPawn->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	float range = currentPawn->GetAttackRange()*0.75;
	FVector loc = H_Relation::LocOfDistanceFromTarget(currentPawn, remain, range);

	//NavMesh 찾기
	auto naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (naviSystem->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	//반환받을 랜덤한 위치.
	FNavLocation randLocation;
	//일정 반경안의 랜덤한 지점을 가져오는 함수
	if (naviSystem->GetRandomPointInNavigableRadius(loc, 20.0f, randLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandPos")), randLocation);

		return EBTNodeResult::Succeeded;
	}



	return EBTNodeResult::Failed;
}
