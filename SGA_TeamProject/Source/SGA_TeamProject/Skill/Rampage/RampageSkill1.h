// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillBase.h"
#include "RampageSkill1.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ARampageSkill1 : public ASkillBase
{
	GENERATED_BODY()
	
public:
	ARampageSkill1();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void DrawSkillAiming() override;
	virtual void DrawSkillPrecaution() override;

	virtual void AITargeting(class ACharacterBase* target = nullptr) override;
	virtual void SkillHit() override;

	virtual void DrawingStart() override;
	virtual void DrawingFinish() override;

private:
	void Section1();
	void Section2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide", meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* _decalComponent2;

	UPROPERTY(EditAnywhere, Category = "Effect")
	class UParticleSystem* _skillEffect;

	UPROPERTY(EditAnywhere, Category = "Effect")
	class UParticleSystem* _hitEffect;
};
