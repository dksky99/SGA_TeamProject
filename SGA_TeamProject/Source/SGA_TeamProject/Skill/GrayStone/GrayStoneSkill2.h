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
	

	// ASkillBase을(를) 통해 상속됨
	void SkillHit() override;

};
