// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "SparrowSkill2.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ASparrowSkill2 : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	// ASkillBase을(를) 통해 상속됨
	virtual void SkillHit() override;
	virtual void DrawSkillAiming() override;

	virtual void DrawSkillPrecaution() override;
	virtual void AITargeting(class ACharacterBase* target = nullptr) override;


	virtual void SetOwner(class ACharacterBase* owner) override;

private:
	void Section1();
	void Section2();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))

	float _delayTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))

	float _attackRadius = 50.0f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectileBase> _projectileClass;

	UPROPERTY()
	TArray<class AProjectileBase*> _projectiles;

	int32 _curFire = 0;

};