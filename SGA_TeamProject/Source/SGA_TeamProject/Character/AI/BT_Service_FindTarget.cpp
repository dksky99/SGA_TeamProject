// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_FindTarget.h"
#include "../../Controller/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "Algo/Sort.h"
#include "../CharacterBase.h"
#include "../../Helper/H_Targetting.h"

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

	//만약 발견하지 못헀을때 가지고있던 타겟이있다면. 타겟을 지우고 행동트리 리셋.
	AActor* remain = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	bool reset = false;
	if (result == false)
	{
		DrawDebugSphere(GetWorld(), pos, detectRadius, 12, FColor::Green, false, 0.3f);
		if (remain)
			reset = true;
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

		if (reset)
			OwnerComp.RestartTree();
		return;
	}
	//발견했다면 가지고있던 타겟이 없다가 생겼으면 타겟을 추가하고 리셋.
	reset = true;
	TArray<AActor*> arr;
	if (remain)
		reset = false;
	for (auto& col : overlapResults)
	{
		if (col.GetActor()->IsValidLowLevel())
		{
			if (remain == col.GetActor())
			{
				if (curPawn->GetTargetChangeFrequently() == false)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), col.GetActor());

					DrawDebugSphere(GetWorld(), pos, detectRadius, 12, FColor::Red, false, 0.3f);
					return;
				}

			

				
			}
			
			arr.Add(col.GetActor());

		}
	}


	remain=H_Targetting::Targetting(curPawn->GetTargetType(), curPawn->GetDefaultTargetType(), arr, remain, curPawn);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), remain);

	DrawDebugSphere(GetWorld(), pos, detectRadius, 12, FColor::Red, false, 0.3f);

	if(reset)
		OwnerComp.RestartTree();

	return;

}


