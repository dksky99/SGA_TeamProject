// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "CharacterAnimInstance.h"
#include "CharacterBase.h"
#include "../Skill/SkillManager.h"
#include "../Skill/SkillBase.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool USkillComponent::DrawSkill1()
{
	if (_owner->IsAttack())
		return false;
	if (_nowUsing != 0)
		return false;
	if (_manager == nullptr)
		return false;
	if (_manager->SkillGuide(1))
	{
		_nowUsing = 1;

		return true;
	}
		return false;

}

bool USkillComponent::AITargetSkill1(ACharacterBase* target)
{
	if (_owner->IsAttack())
		return false;
	if (_nowUsing != 0)
		return false;
	if (_manager == nullptr)
		return false;
	if (_manager->SkillAITarget(1,target))
	{
		_nowUsing = 1;

		return true;
	}
	return false;
}

bool USkillComponent::PlaySkill1()
{

	if (_owner->IsAttack())
		return false;
	if (_nowUsing != 1)
		return false;

	if (_manager == nullptr)
		return false;
	UE_LOG(LogTemp, Log, TEXT(" Ability1"));
	if (_animInstance)
	{
		if (_manager->SkillRelease(1))
		{
			_owner->SetAttack();
			_animInstance->PlayAnimMontage(_firstMontage);
			return true;

		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT(" Ability Time Remain %f"), _manager->GetFirstSkill()->GetRemainCoolTime());
			return false;
		}
	}
	return false;
}

bool USkillComponent::DrawSkill2()
{
	if (_owner->IsAttack())
		return false;
	if (_nowUsing != 0)
		return false;
	if (_manager == nullptr)
		return false;
	if (_manager->SkillGuide(2))
	{
		_nowUsing = 2;

		return true;
	}
	return false;
}

bool USkillComponent::AITargetSkill2(ACharacterBase* target)
{

	if (_owner->IsAttack())
		return false;
	if (_nowUsing != 0)
		return false;
	if (_manager == nullptr)
		return false;
	if (_manager->SkillAITarget(2, target))
	{
		_nowUsing = 2;

		return true;
	}
	return false;
}

bool USkillComponent::PlaySkill2()
{

	if (_owner->IsAttack())
		return false;

	if (_nowUsing != 2)
		return false;
	if (_manager == nullptr)
		return false;
	UE_LOG(LogTemp, Log, TEXT(" Ability1"));
	if (_animInstance)
	{
		if (_manager->SkillRelease(2))
		{
			_nowUsing = 2;
			_owner->SetAttack();
			_animInstance->PlayAnimMontage(_secondMontage);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT(" Ability Time Remain %f"), _manager->GetSecondSkill()->GetRemainCoolTime());
			return false;
			
		}
	}
	return false;
}


void USkillComponent::SkillUsingFinish()
{
	_nowUsing = 0;
	if(_manager)
		_manager->SkillActFinish();


}



// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	_owner = Cast<ACharacterBase>(GetOwner());
	if(_managerClass)
	_manager = GetWorld()->SpawnActor<ASkillManager>(_managerClass,_owner->GetActorLocation(),_owner->GetActorRotation());




	_animInstance = Cast<UCharacterAnimInstance>(_owner->GetMesh()->GetAnimInstance());
	

	if (_manager)
	{
		_manager->AttachToActor(_owner, FAttachmentTransformRules::KeepRelativeTransform);
		_manager->SetOwner(_owner);
		_animInstance->_skill1HitDelegate.AddUObject(_manager->GetFirstSkill(), &ASkillBase::SkillHit);
		_animInstance->_skill2HitDelegate.AddUObject(_manager->GetSecondSkill(), &ASkillBase::SkillHit);
	}

}


