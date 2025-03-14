// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_Attack.h"

#include "../../Controller/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/KismetMathLibrary.h"
#include "../CharacterBase.h"

EBTNodeResult::Type UBT_Task_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto btNodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);


	auto currentPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());


	if (currentPawn->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	if (currentPawn->IsAttack())
		return EBTNodeResult::Failed;

	auto target = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (target->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;

	auto rot = UKismetMathLibrary::FindLookAtRotation(currentPawn->GetActorLocation(), target->GetActorLocation());

	currentPawn->SetActorRotation(rot);

	currentPawn->TryAttack();


	return btNodeResult;
}
