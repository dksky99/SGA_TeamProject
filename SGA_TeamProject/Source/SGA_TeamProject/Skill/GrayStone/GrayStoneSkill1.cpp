// Fill out your copyright notice in the Description page of Project Settings.


#include "GrayStoneSkill1.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
void AGrayStoneSkill1::SkillHit()
{
	UE_LOG(LogTemp, Error, TEXT("Skill1Hit"));


	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _owner->GetAttackRange();
	float attackRadius = 25.0f;
	FVector fwd = _owner->GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = _owner->GetActorLocation();
	FVector end = start + fwd * attackRange;
	FVector center = start + (end - start) * 0.5;

	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;



		FDamageEvent damageEvent;

		hitResult.GetActor()->TakeDamage(_owner->GetStatComponent()->GetAtk(), damageEvent, _owner->Controller, this);


	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);

}

void AGrayStoneSkill1::DrawSkillAiming()
{
	_loc = _owner->GetActorLocation();
	_rot = _owner->GetActorForwardVector().Rotation();

	UE_LOG(LogTemp, Error, TEXT("drawSkill"));
	_decalComponent->SetWorldLocation(_loc);
	_decalComponent->SetWorldRotation(_rot);
}
