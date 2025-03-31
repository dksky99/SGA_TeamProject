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

	bool DrawSkill1();
	bool AITargetSkill1(class ACharacterBase* target);
	bool PlaySkill1();
	bool DrawSkill2();
	bool AITargetSkill2(class ACharacterBase* target);
	bool PlaySkill2();

	void SkillUsingFinish();
	void SetUsingNone() { _nowUsing = 0; }
	bool HasSkill() { return _manager != nullptr; }
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
