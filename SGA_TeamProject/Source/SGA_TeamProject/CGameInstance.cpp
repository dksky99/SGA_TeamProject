// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"

#include "Engine/DataTable.h"
#include "Character/StatComponent.h"

#include "Item/ItemDataTable.h"
#include "Item/ItemManager.h"

UCGameInstance::UCGameInstance()
{
	static::ConstructorHelpers::FObjectFinder<UDataTable> statTable(TEXT("/Script/Engine.DataTable'/Game/Data/CharacterStatTable.CharacterStatTable'"));

	if (statTable.Succeeded())
	{
		_statTable = statTable.Object;
	}

	static::ConstructorHelpers::FObjectFinder<UDataTable> itemTable(TEXT("/Script/Engine.DataTable'/Game/Data/ItemDataTable.ItemDataTable'"));

	if (itemTable.Succeeded())
	{
		_itemTable = itemTable.Object;
	}
}

void UCGameInstance::Init()
{
	Super::Init();

	_itemManager = GetWorld()->SpawnActor<AItemManager>(FVector::ZeroVector, FRotator::ZeroRotator);

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
