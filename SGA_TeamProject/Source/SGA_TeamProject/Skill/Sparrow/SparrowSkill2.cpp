// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowSkill2.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"
#include "../../Character/PlayerCharacter.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
#include "../../Object/ProjectileBase.h"
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



	for (int i = 0; i < 5; i++)
	{
		auto projectile = GetWorld()->SpawnActor<AProjectileBase>(_projectileClass);

		_projectiles.Add(projectile);
	}

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

void ASparrowSkill2::SetOwner(ACharacterBase* owner)
{
	Super::SetOwner(owner);
}

void ASparrowSkill2::Section1()
{
	_curFire = _curFire % _projectiles.Num();

	int32 dmg = _owner->GetStatComponent()->GetAtk();
	_projectiles[_curFire]->SetOwner(_owner);
	_projectiles[_curFire]->SetDamage(dmg);

	_projectiles[_curFire++]->ProjectileFire(_owner->GetMesh()->GetSocketLocation(TEXT("FirePos")), GetActorForwardVector());

	
}

void ASparrowSkill2::Section2()
{
	Section1();
	SkillEnd();
}
