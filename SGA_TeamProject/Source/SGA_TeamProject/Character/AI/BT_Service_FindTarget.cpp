// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_FindTarget.h"
#include "../../Controller/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

#include "../CharacterBase.h"

void UBT_Service_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto  curPawn = Cast<ACharacterBase>( OwnerComp.GetAIOwner()->GetPawn());


	float detectRadius = curPawn->GetDetectRange();


	if (curPawn->IsValidLowLevel() == false)
		return;
	FVector pos = curPawn->GetActorLocation();

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams params(NAME_None, false, curPawn);
	bool result = GetWorld()->OverlapMultiByChannel(
		overlapResults,
		pos,
		FQuat::Identity,
		curPawn->GetChannel(),
		FCollisionShape::MakeSphere(detectRadius),
		params
	);

	if (result == false)
	{
		DrawDebugSphere(GetWorld(), pos, detectRadius, 12, FColor::Green, false, 0.3f);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

		return;
	}

	for (auto& col : overlapResults)
	{
		if (col.GetActor()->IsValidLowLevel())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), col.GetActor());
			DrawDebugSphere(GetWorld(), pos, detectRadius, 12, FColor::Red, false, 0.3f);
			return;

		}
	}

	DrawDebugSphere(GetWorld(), pos, detectRadius, 12, FColor::Green, false, 0.3f);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	return;

}
