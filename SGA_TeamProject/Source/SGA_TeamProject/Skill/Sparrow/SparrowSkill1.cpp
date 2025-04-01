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
	FVector CameraLocation;
	FRotator CameraRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);


}

void ASparrowSkill1::DrawSkillPrecaution()
{
}

void ASparrowSkill1::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);
}
