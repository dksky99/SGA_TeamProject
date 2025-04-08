// Fill out your copyright notice in the Description page of Project Settings.


#include "NarBashSkill1.h"

#include "Engine/DamageEvents.h"
#include "../../Character/StatComponent.h"
#include "../../Character/CharacterBase.h"
#include "../../Character/PlayerCharacter.h"

#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
#include "../AreaObject.h"
#include "../../Helper/H_Targetting.h"
void ANarBashSkill1::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < _attackNum; i++)
	{
		AAreaObject* temp = GetWorld()->SpawnActor<AAreaObject>(_areaClass);
		if (i == _attackNum - 1)
		{

			temp->_endEvent.AddUObject(this, &ANarBashSkill1::Section2);
		}
		else
		{

			temp->_endEvent.AddUObject(this, &ANarBashSkill1::Section1);
		}
		temp->SetScale(_attackRadius * 2.0f, _attackRadius * 2.0f);
		_areas.Add(temp);

		_playSectionTime.Add(i*0.2f);
		FSections temp1;

		temp1.BindUObject(this, &ANarBashSkill1::SpawnArea);
		_playSections.Add(temp1);

	}




	_decalComponent->DecalSize = FVector(_attackRange, _attackRange, 5.0f);

}

void ANarBashSkill1::SkillHit()
{
	Super::SkillHit();
}

void ANarBashSkill1::DrawSkillAiming()
{
	_loc = _owner->GetActorLocation();
	_rot = _owner->GetActorForwardVector().Rotation();
	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);
}


void ANarBashSkill1::DrawSkillPrecaution()
{
}

void ANarBashSkill1::AITargeting(ACharacterBase* target)
{
	Super::AITargeting(target);


	_loc = _owner->GetActorLocation();
	_rot = _owner->GetActorForwardVector().Rotation();
	SetLocOfFloor();

	SetActorLocation(_loc);
	SetActorRotation(_rot);
}

void ANarBashSkill1::Section1()
{
	_curAttack = _curAttack%_areas.Num();
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = _attackRadius;
	FVector fwd = GetActorForwardVector();
	FVector center = _areas[_curAttack++]->GetActorLocation();
	FVector start =  center+ fwd * attackRadius;
	FVector end = center - fwd * attackRadius;
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
				hit.GetActor()->TakeDamage(dmg, damageEvent, _owner->GetController(), _owner);


			}

		}

	}



	//DrawDebugSphere(GetWorld(), center, attackRadius, 32, drawColor, false, 3.0f);

}

void ANarBashSkill1::Section2()
{
	Section1();
	SkillEnd();
	_curAttack = 0;
	_curSpawn = 0;
	_curSection = 0;
}

void ANarBashSkill1::SpawnArea()
{
	_curSpawn=_curSpawn%_areas.Num();
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = _attackRange;
	FVector fwd = GetActorForwardVector();
	FVector center = _owner->GetActorLocation();
	FVector start = center + fwd * attackRadius;
	FVector end = center - fwd * attackRadius;
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
		TArray<AActor*> enemys;
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{

				enemys.Add(hit.GetActor());
				



			}

		}
		AActor* target=H_Targetting::MostLowHpTarget(enemys,nullptr,_owner);
		_loc=target->GetActorLocation();
		SetLocOfFloor();
		_areas[_curSpawn++]->Play(_loc);

	}
	else
	{

		_loc = _owner->GetActorLocation();
		SetLocOfFloor();
		_areas[_curSpawn++]->Play(_loc);
	}



	//DrawDebugSphere(GetWorld(), center, attackRadius, 32, drawColor, false, 3.0f);
}
