// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_FollowLeader.h"
#include "../../Controller/CAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../CharacterBase.h"



EBTNodeResult::Type UBT_Task_FollowLeader::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);


	auto  curPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (curPawn->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	float detectRadius = curPawn->GetDetectRange();


	//현재 리더 찾기
	auto leader = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Leader"))));

	//실패 반환
	if (leader->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;



	FVector pos = leader->GetActorLocation();

	//NavMesh 찾기
	auto naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (naviSystem->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	//반환받을 랜덤한 위치.
	FNavLocation randLocation;
	//일정 반경안의 랜덤한 지점을 가져오는 함수
	if (naviSystem->GetRandomPointInNavigableRadius(pos,detectRadius , randLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandPos")), randLocation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
