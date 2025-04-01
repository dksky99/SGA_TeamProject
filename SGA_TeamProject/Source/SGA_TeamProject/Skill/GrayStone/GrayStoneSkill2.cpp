// Fill out your copyright notice in the Description page of Project Settings.


#include "GrayStoneSkill2.h"


#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
void AGrayStoneSkill2::SkillHit()
{
	Super::SkillHit();
	UE_LOG(LogTemp, Error, TEXT("Skill1Hit"));


	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
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


		ACharacterBase* victim = Cast<ACharacterBase>(hitResult.GetActor());

		FDamageEvent damageEvent;
		int32 dmg = _owner->GetStatComponent()->GetAtk() * 5 + 20;
		victim->TakeDamage(dmg, damageEvent, _owner->Controller, _owner);


	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);
	SkillEnd();
}

void AGrayStoneSkill2::DrawSkillAiming()
{

	FVector start = _owner->GetActorLocation();
	FVector end = start + _owner->GetActorForwardVector() * _attackRange;
	_rot = (end - start).Rotation();
	_loc = start + (end - start) * 0.5f;
	SetLocOfFloor();

	UE_LOG(LogTemp, Error, TEXT("drawSkill"));
	SetActorLocation(_loc);
	SetActorRotation(_rot);
}

void AGrayStoneSkill2::DrawSkillPrecaution()
{

}

void AGrayStoneSkill2::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);
	FVector start = _owner->GetActorLocation();
	FVector end = start + _owner->GetActorForwardVector() * _attackRange;
	_rot = (end - start).Rotation();
	_loc = start + (end - start) * 0.5f;
	SetLocOfFloor();

	UE_LOG(LogTemp, Error, TEXT("drawSkill"));
	SetActorLocation(_loc);
	SetActorRotation(_rot);

}
