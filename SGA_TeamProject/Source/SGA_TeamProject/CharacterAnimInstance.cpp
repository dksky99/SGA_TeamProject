// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "Character/CharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

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

		_vertical = character->MyVertical();
		_horizontal = character->MyHorizontal();
		//_isDead = character->IsDead();
	}
}

void UCharacterAnimInstance::PlayAnimMontage()
{
	if (_animMontage == nullptr)
		return;

	if (!Montage_IsPlaying(_animMontage))
	{
		Montage_Play(_animMontage);
	}
}

void UCharacterAnimInstance::AnimNotify_Attack_Hit()
{
	if (_attackHitDelegate.IsBound())
		_attackHitDelegate.Broadcast();
}

void UCharacterAnimInstance::AnimNotify_Dead()
{
	if (_animDeadEvent.IsBound())
		_animDeadEvent.Broadcast();
}

void UCharacterAnimInstance::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Section%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}
