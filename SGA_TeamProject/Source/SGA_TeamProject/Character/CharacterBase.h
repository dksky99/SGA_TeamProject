// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "CharacterBase.generated.h"

class UInputAction;

struct FInputActionValue;

UCLASS()
class SGA_TEAMPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpDown(float value);
	void RightLeft(float value);

	UFUNCTION()
	void Dead();
	UFUNCTION()
	void DeadActionEnd();

	UFUNCTION()
	void TryAttack();

	UFUNCTION()
	void AttackEnd(class UAnimMontage* Montage, bool bInterrupted);

	float MyVertical() { return _vertical; }
	float MyHorizontal() { return _horizontal; }

	virtual bool CheckEnemy(AActor* target);

	virtual void AttackHit();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void AddHp(int32 value);
	void AddExp(int32 value);

	bool IsAttack() { return _isAttack; }
	float GetAttackRange() { return _attackRange; }

protected:

	//UPROPERTY()
	//class UMyAnimInstance* _animInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = "true"))
	class UStatComponent* _statComponent;

	bool _isAttack = false;
	bool _isUnable = false;

	UPROPERTY()
	class UCharacterAnimInstance* _animInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* _attackAnimMontage;
	
	UPROPERTY(EditAnywhere)
	int32 _maxCombo=1;
	int32 _curAttackSection = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _deadAnimMontage;

	float _vertical = 0;
	float _horizontal = 0;

	UPROPERTY(EditAnywhere)
	float _attackRange = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpBarWidget;
};
