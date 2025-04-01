// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillManager.generated.h"

UCLASS()
class SGA_TEAMPROJECT_API ASkillManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillManager();

	void Set_Owner(class ACharacterBase* owner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool TryUseSkill(int index);

	bool CheckSkillAble(class ASkillBase* skill);
	bool CheckSkillAble(int index);
	bool SkillGuide(int index);
	bool SkillAITarget(int index,class ACharacterBase* target);
	bool SkillRelease(int index);

	void SkillActFinish();
	class ASkillBase* GetFirstSkill() { return _firstAbility; }
	class ASkillBase* GetSecondSkill() { return _secondAbility; }
private:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASkillBase> _firstAbilityClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASkillBase> _secondAbilityClass;


	class ASkillBase* _firstAbility;


	class ASkillBase* _secondAbility;


	class ACharacterBase* _owner = nullptr;

	class ASkillBase* _nowUsing;
	uint32 _nowNum = 0;
	bool _bIsPlaying = false;

};
