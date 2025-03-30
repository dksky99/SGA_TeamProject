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

void USkillComponent::DrawSkill1()
{
	if (_owner->IsAttack())
		return;
	if (_nowUsing != 0)
		return;
	_manager->SkillGuide(1);
	_nowUsing = 1;
}

void USkillComponent::PlaySkill1()
{

	if (_owner->IsAttack())
		return;
	if (_nowUsing != 1)
		return;

	UE_LOG(LogTemp, Log, TEXT(" Ability1"));
	if (_animInstance)
	{
		if (_manager->SkillRelease(1))
		{
			_owner->SetAttack();
			_animInstance->PlayAnimMontage(_firstMontage);

		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT(" Ability Time Remain %f"), _manager->GetFirstSkill()->GetRemainCoolTime());

		}
	}
}

void USkillComponent::DrawSkill2()
{
	if (_owner->IsAttack())
		return;
	if (_nowUsing != 0)
		return;
	_manager->SkillGuide(2);
	_nowUsing = 2;
}

void USkillComponent::PlaySkill2()
{

	if (_owner->IsAttack())
		return;

	if (_nowUsing != 2)
		return;
	UE_LOG(LogTemp, Log, TEXT(" Ability1"));
	if (_animInstance)
	{
		if (_manager->SkillRelease(2))
		{
			_nowUsing = 2;
			_owner->SetAttack();
			_animInstance->PlayAnimMontage(_secondMontage);

		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT(" Ability Time Remain %f"), _manager->GetSecondSkill()->GetRemainCoolTime());
			
		}
	}
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


