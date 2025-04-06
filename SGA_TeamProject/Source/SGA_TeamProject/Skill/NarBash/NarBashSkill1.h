// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "NarBashSkill1.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ANarBashSkill1 : public ASkillBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	// ASkillBase을(를) 통해 상속됨
	virtual void SkillHit() override;
	virtual void DrawSkillAiming() override;

	virtual void DrawSkillPrecaution() override;
	virtual void AITargeting(class ACharacterBase* target = nullptr) override;
	void Section1();
	void Section2();
	void SpawnArea();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AAreaObject> _areaClass;
	TArray<class AAreaObject*> _areas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	int32 _attackNum=20;

	int32 _curAttack = 0;
	int32 _curSpawn = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _attackRadius = 100.0f;

};
