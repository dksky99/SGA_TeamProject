// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(AttackHitDelegate);
DECLARE_MULTICAST_DELEGATE(DeadEvent);


UCLASS()
class SGA_TEAMPROJECT_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCharacterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
	void PlayAnimMontage(UAnimMontage* animMontage);

	UFUNCTION()
	void AnimNotify_Attack_Hit();


	UFUNCTION()
	void AnimNotify_Skill1();


	UFUNCTION()
	void AnimNotify_Skill2();
	UFUNCTION()
	void AnimNotify_Dead();

	void JumpToSection(int32 sectionIndex);

	AttackHitDelegate _attackHitDelegate;
	AttackHitDelegate _skill1HitDelegate;
	AttackHitDelegate _skill2HitDelegate;
	DeadEvent _animDeadEvent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float _speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool _isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	float _vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	float _horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimOffset", meta = (AllowPrivateAccess = "true"))
	float _yaw = 0; // 좌우 회전

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimOffset", meta = (AllowPrivateAccess = "true"))
	float _pitch = 0; // 상하 회전

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimOffset", meta = (AllowPrivateAccess = "true"))
	bool _isTurnLeft = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimOffset", meta = (AllowPrivateAccess = "true"))
	bool _isTurnRight = false;
};
