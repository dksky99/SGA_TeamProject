// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Helper/H_Targetting.h"
#include "CharacterBase.generated.h"

class UInputAction;

struct FInputActionValue;

UENUM()
enum class ECamp
{
	None,
	Player,
	Ally,
	Enemy,
	Max
};



UCLASS()
class SGA_TEAMPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	void PostInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;





	



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
	class UStatComponent* GetStatComponent() { return _statComponent; }

	void DropItem(class AItem* item);

	bool IsAlive();
	bool IsAttack() { return _isAttack; }
	float GetAttackRange() { return _attackRange; }
	float GetDetectRange() { return _detectionRange; }
	ECollisionChannel GetChannel() { return _channel; }
	ECamp GetCamp() { return _camp; }
	int32 GetCurHP();
	void SetCamp(ECamp camp);
	void SetCamp_None();
	void SetCamp_Player();
	void SetCamp_Ally();
	void SetCamp_Enemy();

	class UDamageLoggingComponent* GetLogComponent();
	ETargettingType GetTargetType() { return _targetType; }
	ETargettingType GetDefaultTargetType() { return _defaultTargetType; }
	bool GetTargetChangeFrequently() { return _targetChangeFrequently; }

protected:

	//UPROPERTY()
	//class UMyAnimInstance* _animInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = "true"))
	class UStatComponent* _statComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = "true"))
	class UDamageLoggingComponent* _dmgLogComponent;

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


	UPROPERTY(EditAnywhere)
	float _detectionRange = 800.0f;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Camp",meta=(AllowPrivateAccess ="true"))
	ECamp _camp = ECamp::None;

	ECollisionChannel _channel = ECC_GameTraceChannel2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting", meta = (AllowPrivateAccess = "true"))
	 ETargettingType _targetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting", meta = (AllowPrivateAccess = "true"))
	 ETargettingType _defaultTargetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting", meta = (AllowPrivateAccess = "true"))
	bool _targetChangeFrequently=false;



};
