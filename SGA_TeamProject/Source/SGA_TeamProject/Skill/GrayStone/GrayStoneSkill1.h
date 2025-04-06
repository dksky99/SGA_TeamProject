// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "GrayStoneSkill1.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AGrayStoneSkill1 : public ASkillBase
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
	float _attackRadius = 200.0f;

};
