// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAMPROJECT_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

	void DrawSkill1();
	void PlaySkill1();
	void DrawSkill2();
	void PlaySkill2();

	void SkillUsingFinish();
	void SetUsingNone() { _nowUsing = 0; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	


private:
	class ACharacterBase* _owner;

	class UCharacterAnimInstance* _animInstance;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASkillManager> _managerClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Skill",meta=(AllowPrivateAccess="true"))
	class ASkillManager* _manager;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* _firstMontage;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* _secondMontage;

	int32 _nowUsing = 0;
		
};
