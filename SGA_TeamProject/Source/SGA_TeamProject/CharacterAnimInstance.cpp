// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "CharacterBase.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto pawn = TryGetPawnOwner();
	ACharacterBase* character = Cast<ACharacterBase>(pawn); // dynamicCast
	if (character != nullptr)
	{
		_speed = character->GetVelocity().Size();
		_isFalling = character->GetMovementComponent()->IsFalling();

		_vertical = character->My_Virtical();
		_horizontal = character->My_Horizontal();
		_isDead = character->IsDead();
	}
}

void UCharacterAnimInstance::PlayAnimMontage()
{
}

void UCharacterAnimInstance::AnimNotify_Attack_Hit()
{
}

void UCharacterAnimInstance::AnimNotify_Dead()
{
}

void UCharacterAnimInstance::JumpToSection(int32 sectionIndex)
{
}
