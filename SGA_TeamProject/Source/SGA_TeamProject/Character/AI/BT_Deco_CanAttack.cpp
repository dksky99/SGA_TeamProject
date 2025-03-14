// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_CanAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/CAIController.h"
#include "../CharacterBase.h"
bool UBT_Deco_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (result == false)
		return result;

	auto curPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	auto target = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

	if (curPawn->IsValidLowLevel() == false || target->IsValidLowLevel() == false)
		return false;
	float dist = target->GetDistanceTo(curPawn);

	if (dist < curPawn->GetAttackRange())
		return true;

	return false;
}
