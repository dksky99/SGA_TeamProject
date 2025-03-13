// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

<<<<<<< Updated upstream
#include "CharacterBase.h"
=======
#include "Character/CharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
		_vertical = character->My_Virtical();
		_horizontal = character->My_Horizontal();
		_isDead = character->IsDead();
=======
		_vertical = character->MyVertical();
		_horizontal = character->MyHorizontal();
		//_isDead = character->
>>>>>>> Stashed changes
	}
}

void UCharacterAnimInstance::PlayAnimMontage()
{
<<<<<<< Updated upstream
=======
	if (_animMontage == nullptr)
		return;

	if (!Montage_IsPlaying(_animMontage))
	{
		Montage_Play(_animMontage);
	}
>>>>>>> Stashed changes
}

void UCharacterAnimInstance::AnimNotify_Attack_Hit()
{
<<<<<<< Updated upstream
=======
	if (_attackHitDelegate.IsBound())
		_attackHitDelegate.Broadcast();
>>>>>>> Stashed changes
}

void UCharacterAnimInstance::AnimNotify_Dead()
{
<<<<<<< Updated upstream
=======
	if (_animDeadEvent.IsBound())
		_animDeadEvent.Broadcast();
>>>>>>> Stashed changes
}

void UCharacterAnimInstance::JumpToSection(int32 sectionIndex)
{
<<<<<<< Updated upstream
=======
	FName sectionName = FName(*FString::Printf(TEXT("Section%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
>>>>>>> Stashed changes
}
