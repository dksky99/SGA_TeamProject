// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManager.h"
#include "SkillBase.h"
#include "../Character/CharacterBase.h"

// Sets default values
ASkillManager::ASkillManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkillManager::SetOwner(ACharacterBase* owner)
{
	_owner = owner;
	_firstAbility->SetOwner(owner);
	_secondAbility->SetOwner(owner);
	SetActorLocationAndRotation(owner->GetActorLocation(),owner->GetActorRotation());
	
}

// Called when the game starts or when spawned
void ASkillManager::BeginPlay()
{
	Super::BeginPlay();

	_firstAbility = GetWorld()->SpawnActor<ASkillBase>(_firstAbilityClass, GetActorLocation(), GetActorRotation());
	_secondAbility = GetWorld()->SpawnActor<ASkillBase>(_secondAbilityClass, GetActorLocation(), GetActorRotation());

	
	
}

// Called every frame
void ASkillManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASkillManager::TryUseSkill(int index)
{
	ASkillBase* temp;
	switch (index)
	{
	case 1:
	{
		temp = _firstAbility;
	}
	break;
	case 2:
	{

		temp = _secondAbility;
	}
	break;
	default:
	{
		return false;
	}
	break;
	}
	if (CheckSkillAble(temp))
	{
		_nowUsing = temp;
		_nowNum = index;
		return true;
	}
	return false;
}

bool ASkillManager::CheckSkillAble(ASkillBase* skill)
{
	if (_bIsPlaying)
		return false;
	if (_owner->IsAttack())
		return false;
	if (skill->IsReady() == false)
		return false;
	


	return true;
}

bool ASkillManager::CheckSkillAble(int index)
{
	bool con = false;
	if (index == 1)
		con=CheckSkillAble(_firstAbility);
	else if (index == 2)
		con = CheckSkillAble(_secondAbility);
	return con;
}

bool ASkillManager::SkillGuide(int index)
{
	if (CheckSkillAble(index) == false)
		return false;
	if (TryUseSkill(index) == false)
		return false;

	_nowUsing->StartAiming();
	
	return true;
}

bool ASkillManager::SkillAITarget(int index, class ACharacterBase* target)
{
	if (CheckSkillAble(index) == false)
		return false;
	if (TryUseSkill(index) == false)
		return false;

	_nowUsing->AITargeting(target);

	return true;
}


bool ASkillManager::SkillRelease(int index)
{
	if (CheckSkillAble(index) == false)
		return false;
	if(TryUseSkill(index)==false)
		return false;
	_bIsPlaying = true;
	_nowUsing->SKillBegin();
	return true;
}

void ASkillManager::SkillActFinish()
{
	if(_nowUsing!=nullptr)
		_nowUsing->DrawingFinish();
	_nowUsing = nullptr;
	_bIsPlaying = false;
}


