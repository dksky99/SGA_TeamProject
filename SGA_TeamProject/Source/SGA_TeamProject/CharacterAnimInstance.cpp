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
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	if (pawn)
	{
		ACharacterBase* character = Cast<ACharacterBase>(pawn);
		if (character != nullptr)
		{
			_speed = character->GetVelocity().Size();
			_isFalling = character->GetMovementComponent()->IsFalling();

			_vertical = character->MyVertical();
			_horizontal = character->MyHorizontal();
		}
	}
}

void UCharacterAnimInstance::PlayAnimMontage(UAnimMontage* animMontage)
{
	if (!Montage_IsPlaying(animMontage))
	{
		Montage_Play(animMontage);
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
