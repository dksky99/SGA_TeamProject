// Fill out your copyright notice in the Description page of Project Settings.


#include "NarBashSkill2.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"
#include "../../Character/PlayerCharacter.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
#include "../../Object/ProjectileMultiple.h"
void ANarBashSkill2::BeginPlay()
{
	Super::BeginPlay();
	_decalComponent->DecalSize = FVector(_attackRange * 0.5, _attackRadius, 5.0f);
	_projectile = GetWorld()->SpawnActor<AProjectileMultiple>(_projectileClass);
}

void ANarBashSkill2::SkillHit()
{
	Super::SkillHit();

	_projectile->SetOwner(_owner);
	int32 dmg = _owner->GetStatComponent()->GetAtk() * 1.5f + 10;
	_projectile->SetDamage(dmg);
	FVector temp;
	if (_target)
	{
		FVector start = _owner->GetActorLocation();
		temp = _target->GetActorLocation();
		temp.Z = start.Z;
		temp = temp - start;
		temp.Normalize();
	}
	else
		temp = _owner->GetActorForwardVector();

	_projectile->ProjectileFire(_owner->GetActorLocation(), temp);

	UE_LOG(LogTemp, Error, TEXT("BossProjectile"));

	SkillEnd();
}

void ANarBashSkill2::DrawSkillAiming()
{
}

void ANarBashSkill2::DrawSkillPrecaution()
{

	FVector start = _owner->GetActorLocation();
	FVector temp = _target->GetActorLocation();
	temp.Z = start.Z;
	temp = temp - start;
	temp.Normalize();
	FVector end = start + temp * _attackRange;
	_rot = (end - start).Rotation();
	_loc = start + (end - start) * 0.5f;
	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);
}

void ANarBashSkill2::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);
	_target = target;
	FVector start = _owner->GetActorLocation();
	FVector temp = target->GetActorLocation();
	temp.Z = start.Z;
	temp = temp - start;
	temp.Normalize();
	FVector end = start + temp * _attackRange;
	_rot = (end - start).Rotation();
	_loc = start + (end - start) * 0.5f;
	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);

}
