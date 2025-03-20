// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageLoggingComponent.h"
#include "CharacterBase.h"
#include "Algo/MaxElement.h"
#include "Algo/Sort.h"

// Sets default values for this component's properties
UDamageLoggingComponent::UDamageLoggingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDamageLoggingComponent::Logging(ACharacterBase* causer, int32 damage)
{
	if (!causer) return;  
	curTime = 0.0f;
	int32* dmg = _damageLog.Find(causer);  // causer가 존재하는지 확인
	if (dmg)
	{
		*dmg += damage;
	}
	else
	{
		_damageLog.Add(causer, damage);  // 처음 추가하는 경우
	}
}

ACharacterBase* UDamageLoggingComponent::GetBestDamageCauser()
{
	if (_damageLog.IsEmpty())
		return nullptr;
	auto best=Algo::MaxElementBy(_damageLog, [](const TPair<AActor*, int32>& Pair) { return Pair.Value; });

	return best->Key;
}

const TMap<class ACharacterBase*, int32>& UDamageLoggingComponent::GetLog()
{
	return _damageLog;
}

TArray<TPair<class ACharacterBase*, int32>> UDamageLoggingComponent::GetValidList()
{
	if (_damageLog.Num() == 0)
	{
		return  TArray<TPair<class ACharacterBase*, int32>>(); 
	}
	TArray<TPair<ACharacterBase*, int32>> DamageArray;
	for (const auto& Pair : _damageLog)
	{
		if (Pair.Key->IsAlive())
		{
			DamageArray.Add(Pair);

		}

	}

	Algo::Sort(DamageArray, [](const TPair<ACharacterBase*, int32>& A, const TPair<ACharacterBase*, int32>& B)
		{
			return A.Value > B.Value;
		});
	return DamageArray;
}



// Called when the game starts
void UDamageLoggingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDamageLoggingComponent::EraseLog()
{
	_damageLog.Empty();
}


// Called every frame
void UDamageLoggingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	curTime += DeltaTime;

	if (curTime > resetTime)
	{
		curTime = 0.0f;
		EraseLog();
	}
	// ...
}

