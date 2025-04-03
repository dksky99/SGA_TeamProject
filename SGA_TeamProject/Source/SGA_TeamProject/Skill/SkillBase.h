// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"


UENUM()
enum class ESkillState
{
	Deactivate=0,
	Aiming,
	Precaution,
	Playing,
	Max

};

DECLARE_DELEGATE(FSections)


UCLASS()
class SGA_TEAMPROJECT_API ASkillBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//플레이어가 스킬 시전을위해 장판을 보고 위치를 설정
	void StartAiming();
	void StartPreCaution();
	
	void DrawingStart();
	void DrawingFinish();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//AI가 타겟을 통해 스킬을 시전할 위치를 설정
	// override후에 부모 함수 호출을 해주기
	virtual void AITargeting(class ACharacterBase* target = nullptr);
	//플레이어가 스킬을 사용할 범위를 그림
	virtual void DrawSkillAiming() ;
	//범위 지정이 완료되어 그 위치에 전조 장판을 그림.
	virtual void DrawSkillPrecaution() ;

	//스킬의 입력이 들어갔고 모션을 시작함.
	// override후에 부모 함수 호출을 해주기

	virtual void SKillBegin();

	//스킬의 작동이 시작됨. override후에 부모 함수 호출을 해주기
	virtual void SkillHit() ;
	//작동이 시작한 후로 지속적으로 호출되는 함수. 이를 통해 일정시간 간격으로 시전되는 다단계 스킬을 구현가능.
	virtual void SkillTick();

	//스킬 동작이 완전히 끝남. 반드시 스킬 틱을 통해 순서대로 호출되는 함수 마지막에 꼭 호출해주기.
	// override후에 부모 함수 호출을 해주기
	virtual void SkillEnd();

	bool CheckSection();

	float GetCoolTimeRatio() { return _curTime / _coolTime; }
	float GetRemainCoolTime() { return _coolTime - _curTime; }
	bool IsReady() { return _curTime >= _coolTime; }

	void SetOwner(class ACharacterBase* owner);
	void SetLocOfFloor();
	ESkillState GetState() { return _state; }
 private:
	void TimeFlow(float DeltaTime);
	
protected:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* _sceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Guide",meta=(AllowPrivateAccess="true"))
	class UDecalComponent* _decalComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide", meta = (AllowPrivateAccess = "true"))
	class USplineComponent* _splineComponent;

	class ACharacterBase* _owner;

	class ACharacterBase* _target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _coolTime=1.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _curTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _playTime=0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _precautionTime=0.0f;


	ESkillState _state;

	FVector _loc;
	FRotator _rot;

	bool _bIsDrawing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _attackRange=0.0f;

	TArray<FSections> _playSections;
	TArray<float> _playSectionTime;
	int32 _curSection = 0;




};
