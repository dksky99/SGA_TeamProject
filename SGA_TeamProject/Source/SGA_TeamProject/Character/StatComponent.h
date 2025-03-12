// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"


USTRUCT()
struct FCharacterStatData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 atk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 exp;

};

DECLARE_MULTICAST_DELEGATE_OneParam(FHpChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FExpChanged, int32);
DECLARE_MULTICAST_DELEGATE(FDeadEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAMPROJECT_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GetData(int value);
	int32 GetCurHp() { return _curHp; }
	int32 GetAtk() { return _atk; }
	int32 AddCurHp(float amount, AActor* causer = nullptr);
	float GetSpeed() { return _speed; }

	bool IsDead() { return _curHp <= 0; }

	void AddExp(int32 value);
	bool CheckLevelUp();
	void LevelUp();


	FHpChanged _hpChanged;
	FExpChanged _expChanged;
	FDeadEvent _deadEvent;
private:
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 _level = 1;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 _curHp = 100;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 _maxHp = 100;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 _atk = 10;


	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	float _speed = 10;

	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 _curExp = 0;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 _maxExp;

	AActor* _owner;
		
};
