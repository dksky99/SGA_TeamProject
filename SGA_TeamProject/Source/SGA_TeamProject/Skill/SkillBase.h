// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"


UENUM()
enum class ESkillState
{
	Deactivate=0,
	Precaution,
	Aiming,
	Playing,
	Max

};

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
	void StartAiming();
	void StartPreCaution(class ACharacterBase* target=nullptr);
	void FinishAiming();
	
	void DrawingStart();
	void DrawingFinish();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DrawSkillAiming() ;
	virtual void DrawSkillPrecaution() ;

	virtual void SKillBegin();

	virtual void SkillHit() ;
	virtual void SkillTick();

	virtual void SkillEnd();

	float GetCoolTimeRatio() { return _curTime / _coolTime; }
	float GetRemainCoolTime() { return _coolTime - _curTime; }
	bool IsReady() { return _curTime >= _coolTime; }

	void SetOwner(class ACharacterBase* owner);
	void SetLocOfFloor();
	ESkillState GetState() { return _state; }
 private:
	void CoolTimeFlow(float DeltaTime);
	
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
	
	float _curTime;


	ESkillState _state;

	FVector _loc;
	FRotator _rot;

	bool _bIsDrawing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	float _attackRange=0.0f;



};
