// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "NarBashSkill2.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ANarBashSkill2 : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	// ASkillBase을(를) 통해 상속됨
	virtual void SkillHit() override;
	virtual void DrawSkillAiming() override;

	virtual void DrawSkillPrecaution() override;
	virtual void AITargeting(class ACharacterBase* target = nullptr) override;


private:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _attackRadius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectileMultiple> _projectileClass;
	class AProjectileMultiple* _projectile;
};
