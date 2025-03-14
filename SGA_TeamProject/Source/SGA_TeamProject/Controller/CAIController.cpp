// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


ACAIController::ACAIController()
{
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* temp = Blackboard;

	if (UseBlackboard(_blackBoard, temp))
	{

		if (RunBehaviorTree(_behaviorTree))
		{

		}
		else
		{

			UE_LOG(LogTemp, Error, TEXT("BT_Failed"));
		}



	}
	else
	{

		UE_LOG(LogTemp, Error, TEXT("BB_Failed"));
	}
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::RandMove()
{


	auto curPawn = GetPawn();
	if (curPawn->IsValidLowLevel() == false)
		return;

	auto navMesh = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (navMesh->IsValidLowLevel() == false)
		return;

	//반환받을 랜덤한 위치.
	FNavLocation randLocation;
	FVector pawnLocation = curPawn->GetActorLocation();
	if (navMesh->GetRandomPointInNavigableRadius(pawnLocation, 500.0f, randLocation))
	{

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation.Location);

	}
}
