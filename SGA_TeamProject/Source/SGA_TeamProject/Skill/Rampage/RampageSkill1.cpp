// Fill out your copyright notice in the Description page of Project Settings.


#include "RampageSkill1.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/DecalComponent.h"

#include "../../Character/CharacterBase.h"
#include "../../Character/StatComponent.h"

ARampageSkill1::ARampageSkill1()
{
	_decalComponent2 = CreateDefaultSubobject<UDecalComponent>("Decal2");
	_decalComponent2->SetupAttachment(RootComponent);

	_decalComponent->SetRelativeLocation(FVector(0, -70, -88));
	_decalComponent2->SetRelativeLocation(FVector(0, 70, -88));
}

void ARampageSkill1::BeginPlay()
{
	Super::BeginPlay();

	_playSectionTime.Add(0.0f);
	_playSectionTime.Add(0.25f);

	FSections temp1, temp2;
	temp1.BindUObject(this, &ARampageSkill1::Section1);
	temp2.BindUObject(this, &ARampageSkill1::Section2);

	_playSections.Add(temp1);
	_playSections.Add(temp2);
}

void ARampageSkill1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARampageSkill1::DrawSkillAiming()
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

void ARampageSkill1::DrawSkillPrecaution()
{
}

void ARampageSkill1::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);
	
	DrawSkillAiming();
}

void ARampageSkill1::SkillHit()
{
	Super::SkillHit();
	UE_LOG(LogTemp, Error, TEXT("Skill1Hit"));

}

void ARampageSkill1::Section1()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = 25.0f;
	FVector fwd = _owner->GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = _owner->GetActorLocation() + _owner->GetActorRightVector() * 70.0f;
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

	if (_skillEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			_skillEffect,
			center,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true
		);
	}

	FColor drawColor = FColor::Green;
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		ACharacterBase* victim = Cast<ACharacterBase>(hitResult.GetActor());
		FDamageEvent damageEvent;

		int32 dmg = _owner->GetStatComponent()->GetAtk() * 2 + 10;
		victim->TakeDamage(dmg, damageEvent, _owner->Controller, _owner);

		if (_hitEffect)
		{
			FVector hitPoint = hitResult.ImpactPoint;

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

	//DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);
}

void ARampageSkill1::Section2()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = 25.0f;
	FVector fwd = _owner->GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = _owner->GetActorLocation() - _owner->GetActorRightVector() * 70.0f;
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

	if (_skillEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			_skillEffect,
			center,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true
		);
	}

	FColor drawColor = FColor::Green;
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		ACharacterBase* victim = Cast<ACharacterBase>(hitResult.GetActor());
		FDamageEvent damageEvent;

		int32 dmg = _owner->GetStatComponent()->GetAtk() * 2 + 10;
		victim->TakeDamage(dmg, damageEvent, _owner->Controller, _owner);

		if (_hitEffect)
		{
			FVector hitPoint = hitResult.ImpactPoint;

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

	//DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);
	SkillEnd();
}

void ARampageSkill1::DrawingStart()
{
	Super::DrawingStart();
	_decalComponent2->SetActive(true);
	_decalComponent2->SetVisibility(true);
}

void ARampageSkill1::DrawingFinish()
{
	Super::DrawingFinish();
	_decalComponent2->SetActive(false);
	_decalComponent2->SetVisibility(false);
}