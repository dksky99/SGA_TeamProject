// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowSkill1.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"
#include "../../Character/PlayerCharacter.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"

ASparrowSkill1::ASparrowSkill1()
{
}

void ASparrowSkill1::BeginPlay()
{
	Super::BeginPlay();
	_playSectionTime.Add(0.5f);
	_playSectionTime.Add(1.0f);
	_playSectionTime.Add(2.0f);

	FSections temp1,temp2,temp3;
	temp1.BindUObject(this, &ASparrowSkill1::Section1);
	temp2.BindUObject(this, &ASparrowSkill1::Section2);
	temp3.BindUObject(this, &ASparrowSkill1::Section3);
	_playSections.Add(temp1);
	_playSections.Add(temp2);
	_playSections.Add(temp3);

	_decalComponent->DecalSize = FVector(_radius, _radius, 5.0f);
}

void ASparrowSkill1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASparrowSkill1::SkillHit()
{
	Super::SkillHit();
	DrawingStart();

}

void ASparrowSkill1::DrawSkillAiming()
{
	FVector		cameraLocation;
	FRotator	cameraRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(cameraLocation, cameraRotation);

	float p = cameraRotation.Pitch - _minAngle;
	p = FMath::Clamp(p, 0.0f, _maxAngle - _minAngle);
	float dist = _minRange + (_maxRange - _minRange) * (p / (_maxAngle - _minAngle));
	_loc = _owner->GetActorLocation()+_owner->GetActorForwardVector() * dist;
	_rot = _owner->GetActorForwardVector().Rotation();
	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);
}

void ASparrowSkill1::DrawSkillPrecaution()
{
}

void ASparrowSkill1::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);

	_loc = target->GetActorLocation();
	_rot = _owner->GetActorForwardVector().Rotation();
	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);
}

void ASparrowSkill1::Section1()
{
	DrawingFinish();
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 100;
	FVector fwd = GetActorForwardVector();
	FVector start = _loc + fwd * attackRadius;
	FVector end = _loc - fwd * attackRadius ;
	FVector center = _loc;
	FQuat qRot = FQuat::FindBetweenVectors(start, end);

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{



				FDamageEvent damageEvent;
				int32 dmg = _owner->GetStatComponent()->GetAtk() * 1 + 10;
				hit.GetActor()->TakeDamage(dmg, damageEvent, _owner->GetController(), this);


			}

		}

	}

	UE_LOG(LogTemp, Error, TEXT("BossAttack %f %f %f"), center.X, center.Y, center.Z);


	DrawDebugSphere(GetWorld(), center, attackRadius ,32 , drawColor, false, 3.0f);

}

void ASparrowSkill1::Section2()
{
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 150;
	FVector fwd = GetActorForwardVector();
	FVector start = _loc + fwd * attackRadius;
	FVector end = _loc - fwd * attackRadius;
	FVector center = _loc;
	FQuat qRot = FQuat::FindBetweenVectors(start, end);

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{



				FDamageEvent damageEvent;
				int32 dmg = _owner->GetStatComponent()->GetAtk() * 1 + 15;
				hit.GetActor()->TakeDamage(dmg, damageEvent, _owner->GetController(), this);


			}

		}

	}

	UE_LOG(LogTemp, Error, TEXT("BossAttack %f %f %f"), center.X, center.Y, center.Z);


	DrawDebugSphere(GetWorld(), center, attackRadius, 32, drawColor, false, 3.0f);

}

void ASparrowSkill1::Section3()
{
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 200;
	FVector fwd = GetActorForwardVector();
	FVector start = _loc + fwd * attackRadius;
	FVector end = _loc - fwd * attackRadius;
	FVector center = _loc;
	FQuat qRot = FQuat::FindBetweenVectors(start, end);

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{



				FDamageEvent damageEvent;
				int32 dmg = _owner->GetStatComponent()->GetAtk() * 1 + 5;
				hit.GetActor()->TakeDamage(dmg, damageEvent, _owner->GetController(), this);


			}

		}

	}

	UE_LOG(LogTemp, Error, TEXT("BossAttack %f %f %f"), center.X, center.Y, center.Z);


	DrawDebugSphere(GetWorld(), center, attackRadius, 32, drawColor, false, 3.0f);

	SkillEnd();
}
