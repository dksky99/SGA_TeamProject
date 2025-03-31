// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "GrayStoneSkill2.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AGrayStoneSkill2 : public ASkillBase
{
	GENERATED_BODY()
	

	virtual void SkillHit() override;
	virtual void DrawSkillAiming() override;

	virtual void DrawSkillPrecaution() override;
	virtual void AITargeting(class ACharacterBase* target = nullptr) override;

};
