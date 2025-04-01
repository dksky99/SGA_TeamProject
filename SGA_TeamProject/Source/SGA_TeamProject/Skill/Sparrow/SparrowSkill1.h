// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "SparrowSkill1.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ASparrowSkill1 : public ASkillBase
{
	GENERATED_BODY()

public:


	// ASkillBase을(를) 통해 상속됨
	virtual void SkillHit() override;
	virtual void DrawSkillAiming() override;

	virtual void DrawSkillPrecaution() override;
	virtual void AITargeting(class ACharacterBase* target = nullptr) override;

private:

	float MinRange = 200.0f; // 최소 사거리
	float MaxRange = 1000.0f; // 최대 사거리
	float PitchAngle = 45.0f; // 위로 올리는 각도 (도 단위)


};
