// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"

#include "Character/StatComponent.h"
#include "Item/ItemManager.h"

UCGameInstance::UCGameInstance()
{
}

void UCGameInstance::Init()
{
	Super::Init();

	if (_itemManagerClass)
	{
		_itemManager = GetWorld()->SpawnActor<AItemManager>(_itemManagerClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}
}

FCharacterStatData UCGameInstance::GetStat_Level(int32 level)
{
	FString rowName = "Level_" + FString::FromInt(level);
	auto row = _statTable->FindRow<FCharacterStatData>(*rowName, TEXT(""));
	return *row;
}

FItemData UCGameInstance::GetItemData_ID(int32 id)
{
	FString rowName = FString::FromInt(id);
	auto row = _itemTable->FindRow<FItemData>(*rowName, TEXT(""));
	return *row;
}
