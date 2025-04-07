// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_FollowLeader.h"
#include "../../Controller/CAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../CharacterBase.h"
#include "../../Helper/H_Relation.h"


UBT_Task_FollowLeader::UBT_Task_FollowLeader()
{

	NodeName = TEXT("Move To Leader ");
	bNotifyTick = true;
}

EBTNodeResult::Type UBT_Task_FollowLeader::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//현재 빙의된 Pawn 찾기
	auto currentPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	auto leader = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Leader"))));
	//실패 반환
	if (currentPawn->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	if (leader->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;



	OwnerComp.GetAIOwner()->MoveToActor(leader, 200.0f, true);



	return EBTNodeResult::InProgress;

	//현재 리더 찾기
}

void UBT_Task_FollowLeader::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!AIController || !BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	//현재 빙의된 Pawn 찾기
	auto currentPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	auto leader = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Leader"))));
	//실패 반환
	if (currentPawn->IsValidLowLevel() == false || leader->IsValidLowLevel() == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	float Distance = FVector::Dist(leader->GetActorLocation(), currentPawn->GetActorLocation());

	if (Distance <= currentPawn->GetDetectRange() * 0.5f)
	{
		AIController->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
