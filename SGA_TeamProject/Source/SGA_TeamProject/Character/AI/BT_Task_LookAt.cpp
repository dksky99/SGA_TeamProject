// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_LookAt.h"

#include "../../Controller/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/KismetMathLibrary.h"
#include "../CharacterBase.h"

EBTNodeResult::Type UBT_Task_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto btNodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);


	auto currentPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());


	if (currentPawn->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;
	if(currentPawn->IsAttack())
		return EBTNodeResult::Failed;


	auto target = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (target->IsValidLowLevel() == false)
		return EBTNodeResult::Failed;
	FRotator curRot = currentPawn->GetActorRotation();

	FRotator targetRot = UKismetMathLibrary::FindLookAtRotation(
		currentPawn->GetActorLocation(), target->GetActorLocation()
	);
	targetRot.Pitch = 0.0f;
	targetRot.Roll = 0.0f;

	// 부드럽게 회전 (DeltaTime과 RotationSpeed 반영)
	float RotationSpeed = 10.0f;  // 회전 속도 (더 낮추면 천천히 돔)
	FRotator newRot = FMath::RInterpTo(curRot, targetRot, GetWorld()->GetDeltaSeconds(), RotationSpeed);

	currentPawn->SetActorRotation(newRot);



	return btNodeResult;
}
