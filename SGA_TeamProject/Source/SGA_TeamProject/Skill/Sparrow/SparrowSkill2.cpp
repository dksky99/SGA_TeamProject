// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowSkill2.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"
#include "../../Character/PlayerCharacter.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
void ASparrowSkill2::BeginPlay()
{
	Super::BeginPlay();
	_playSectionTime.Add(1.0f);
	_playSectionTime.Add(1.1f);
	_playSectionTime.Add(1.2f);
	_playSectionTime.Add(1.3f);
	_playSectionTime.Add(1.4f);

	FSections temp1, temp2, temp3,temp4,temp5;
	temp1.BindUObject(this, &ASparrowSkill2::Section1);
	temp2.BindUObject(this, &ASparrowSkill2::Section1);
	temp3.BindUObject(this, &ASparrowSkill2::Section1);
	temp4.BindUObject(this, &ASparrowSkill2::Section1);
	temp5.BindUObject(this, &ASparrowSkill2::Section2);
	_playSections.Add(temp1);
	_playSections.Add(temp2);
	_playSections.Add(temp3);
	_playSections.Add(temp4);
	_playSections.Add(temp5);

	_decalComponent->DecalSize = FVector(_attackRange * 0.5, _attackRadius, 5.0f);
}

void ASparrowSkill2::SkillHit()
{
	Super::SkillHit();
}

void ASparrowSkill2::DrawSkillAiming()
{


	FVector		cameraLocation;
	FRotator	cameraRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(cameraLocation, cameraRotation);
	FRotator temp = _owner->GetActorForwardVector().Rotation();
	temp.Yaw = cameraRotation.Yaw;
	
	FVector start = _owner->GetActorLocation();
	FVector end = start + temp.Vector() * _attackRange;
	_rot = (end - start).Rotation();
	_loc = start + (end - start) * 0.5f;
	SetLocOfFloor();

	UE_LOG(LogTemp, Error, TEXT("drawSkill"));
	SetActorLocation(_loc);
	SetActorRotation(_rot);
}

void ASparrowSkill2::DrawSkillPrecaution()
{
}

void ASparrowSkill2::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);
	FVector start = _owner->GetActorLocation();
	FVector end = start + _owner->GetActorForwardVector() * _attackRange;
	_rot = (end - start).Rotation();
	_loc = start + (end - start) * 0.5f;
	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);

}

void ASparrowSkill2::Section1()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = _attackRadius;
	FVector fwd = _owner->GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = _owner->GetMesh()->GetSocketLocation(TEXT("FirePos"));

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
		int32 dmg = _owner->GetStatComponent()->GetAtk() * 1 + 5;
		victim->TakeDamage(dmg, damageEvent, _owner->Controller, _owner);


	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);
	
}

void ASparrowSkill2::Section2()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = _attackRadius;
	FVector fwd = _owner->GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);

	FVector start = _owner->GetMesh()->GetSocketLocation(TEXT("FirePos"));
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
		int32 dmg = _owner->GetStatComponent()->GetAtk() * 2 + 10;
		victim->TakeDamage(dmg, damageEvent, _owner->Controller, _owner);


	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);
	SkillEnd();
}
