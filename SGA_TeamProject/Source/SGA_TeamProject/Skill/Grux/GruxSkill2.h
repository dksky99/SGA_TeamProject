// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "GruxSkill2.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AGruxSkill2 : public ASkillBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SkillHit() override;
	void MultiHit(int32 damageScale, int32 baseDamage);
	virtual void DrawSkillAiming() override;

	virtual void DrawSkillPrecaution() override;
	virtual void AITargeting(class ACharacterBase* target = nullptr) override;

private:
	float _delayTime = 1.0f;
};
