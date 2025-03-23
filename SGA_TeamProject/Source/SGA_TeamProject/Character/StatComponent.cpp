// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "CharacterBase.h"
#include "../CGameInstance.h"
// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	GetData(_level);
	
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatComponent::GetData(int value)
{
	auto gameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());
	auto statInfo = gameInstance->GetStat_Level(value);

	_maxHp = statInfo.hp;
	_curHp = _maxHp;
	_atk = statInfo.atk;
	_maxExp = statInfo.exp;
}

int32 UStatComponent::AddCurHp(float amount, AActor* causer)
{
	int32 before = _curHp;
	_curHp += amount;


	if (_curHp < 0)
	{
		_curHp = 0;
	}
	if (_curHp > _maxHp)
		_curHp = _maxHp;



	UE_LOG(LogTemp, Log, TEXT(" Name :%s ,HP : %df"), *(GetOwner()->GetName()), _curHp);

	float ratio = _curHp / (float)_maxHp;
	if (_hpChanged.IsBound())
	{
		_hpChanged.Broadcast(ratio);
	}
	return before - _curHp;
}

void UStatComponent::AddExp(int32 value)
{
	_curExp += value;
	CheckLevelUp();
}

bool UStatComponent::CheckLevelUp()
{
	UE_LOG(LogTemp, Log, TEXT(" Check Level Up"));
	if (_maxExp <= _curExp)
	{
		_curExp -= _maxExp;
		LevelUp();
		CheckLevelUp();
		return true;
	}
	return false;
}

void UStatComponent::LevelUp()
{
	_level += 1;
	GetData(_level);

	UE_LOG(LogTemp, Log, TEXT(" Level Up"));
}

