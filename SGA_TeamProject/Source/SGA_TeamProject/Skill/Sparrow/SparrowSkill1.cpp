// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowSkill1.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"
#include "../../Character/PlayerCharacter.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"

void ASparrowSkill1::SkillHit()
{
	Super::SkillHit();
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
	
}
