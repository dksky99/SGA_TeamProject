// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxSkill2.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"


void AGruxSkill2::BeginPlay()
{
	Super::BeginPlay();
	_playSectionTime.Add(0.8f);
	_playSectionTime.Add(0.9f);
	_playSectionTime.Add(1.0f);

	FSections temp1, temp2, temp3;
	temp1.BindLambda([this]() {MultiHit(3, 20); });
	temp2.BindLambda([this]() {MultiHit(4, 30); });
	temp3.BindLambda([this]() {MultiHit(5, 40); });
	_playSections.Add(temp1);
	_playSections.Add(temp2);
	_playSections.Add(temp3);
}

void AGruxSkill2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGruxSkill2::SkillHit()
{
	Super::SkillHit();
}

void AGruxSkill2::MultiHit(int32 damageScale, int32 baseDamage)
{
	UE_LOG(LogTemp, Error, TEXT("MultiHit"));

	TArray<FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = 200.0f;
	FVector fwd = _owner->GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = _owner->GetActorLocation();
	FVector end = start + fwd * attackRange;
	FVector center = start + (end - start) * 0.5;

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (const auto& hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{
				ACharacterBase* victim = Cast<ACharacterBase>(hit.GetActor());
				FDamageEvent damageEvent;

				int32 dmg = _owner->GetStatComponent()->GetAtk() * damageScale + baseDamage;
				victim->TakeDamage(dmg, damageEvent, _owner->Controller, _owner);
			}
		}
	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);
}

void AGruxSkill2::DrawSkillAiming()
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

void AGruxSkill2::DrawSkillPrecaution()
{
}

void AGruxSkill2::AITargeting(ACharacterBase* target)
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
