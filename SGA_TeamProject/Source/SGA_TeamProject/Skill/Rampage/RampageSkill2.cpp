// Fill out your copyright notice in the Description page of Project Settings.


#include "RampageSkill2.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "../../Character/CharacterBase.h"
#include "../../Character/StatComponent.h"

void ARampageSkill2::BeginPlay()
{
	Super::BeginPlay();

	_playSectionTime.Add(0.0f);
	_playSectionTime.Add(2.5f);
	_playSectionTime.Add(5.0f);

	FSections temp1, temp2, temp3;
	temp1.BindUObject(this, &ARampageSkill2::Section1);
	temp2.BindUObject(this, &ARampageSkill2::Section2);
	temp3.BindUObject(this, &ARampageSkill2::Section3);

	_playSections.Add(temp1);
	_playSections.Add(temp2);
	_playSections.Add(temp3);

}

void ARampageSkill2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARampageSkill2::DrawSkillAiming()
{
	_loc = _owner->GetActorLocation() + _owner->GetActorForwardVector() * 500.0f;
	_rot = _owner->GetActorForwardVector().Rotation();

	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);
}

void ARampageSkill2::DrawSkillPrecaution()
{
}

void ARampageSkill2::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);
	
	DrawSkillAiming();
}

void ARampageSkill2::SkillHit()
{
	Super::SkillHit();

}

void ARampageSkill2::Section1()
{
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 110.0f;
	FVector fwd = GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(_loc, _loc);

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		_loc,
		_loc,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	if (_skillEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			_skillEffect,
			_loc,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true
		);
	}

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{
				FDamageEvent damageEvent;
				int32 dmg = _owner->GetStatComponent()->GetAtk() * 2 + 10;
				hit.GetActor()->TakeDamage(dmg, damageEvent, _owner->GetController(), _owner);
				
				if (_hitEffect)
				{
					FVector hitPoint = hit.ImpactPoint;

					UGameplayStatics::SpawnEmitterAtLocation
					(
						GetWorld(),
						_hitEffect,
						hitPoint,
						FRotator::ZeroRotator,
						FVector(1.0f),
						true
					);
				}
			}
		}
	}

	//DrawDebugSphere(GetWorld(), _loc, attackRadius, 32, drawColor, false, 3.0f);
}

void ARampageSkill2::Section2()
{
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 150.0f;
	FVector fwd = GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(_loc, _loc);

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		_loc,
		_loc,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	if (_skillEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			_skillEffect,
			_loc,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true
		);
	}

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{
				FDamageEvent damageEvent;
				int32 dmg = _owner->GetStatComponent()->GetAtk() * 3 + 10;
				hit.GetActor()->TakeDamage(dmg, damageEvent, _owner->GetController(), _owner);
			
				if (_hitEffect)
				{
					FVector hitPoint = hit.ImpactPoint;

					UGameplayStatics::SpawnEmitterAtLocation
					(
						GetWorld(),
						_hitEffect,
						hitPoint,
						FRotator::ZeroRotator,
						FVector(1.0f),
						true
					);
				}
			}
		}
	}

	//DrawDebugSphere(GetWorld(), _loc, attackRadius, 32, drawColor, false, 3.0f);
}

void ARampageSkill2::Section3()
{
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 200.0f;
	FVector fwd = GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(_loc, _loc);

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		_loc,
		_loc,
		FQuat::Identity,
		_owner->GetChannel(),
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	if (_skillEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			_skillEffect,
			_loc,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true
		);
	}

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{
				FDamageEvent damageEvent;
				int32 dmg = _owner->GetStatComponent()->GetAtk() * 5 + 10;
				hit.GetActor()->TakeDamage(dmg, damageEvent, _owner->GetController(), _owner);
			
				if (_hitEffect)
				{
					FVector hitPoint = hit.ImpactPoint;

					UGameplayStatics::SpawnEmitterAtLocation
					(
						GetWorld(),
						_hitEffect,
						hitPoint,
						FRotator::ZeroRotator,
						FVector(1.0f),
						true
					);
				}
			}
		}
	}

	//DrawDebugSphere(GetWorld(), _loc, attackRadius, 32, drawColor, false, 3.0f);
	SkillEnd();
}
