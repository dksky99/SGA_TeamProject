// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"
#include "Character/StatComponent.h"
#include "Engine/DataTable.h"

UCGameInstance::UCGameInstance()
{
	static::ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("/Script/Engine.DataTable'/Game/Data/CharacterStatTable.CharacterStatTable'"));

	if (dataTable.Succeeded())
	{
		_statTable = dataTable.Object;

	}
}

void UCGameInstance::Init()
{
	Super::Init();
}

FCharacterStatData UCGameInstance::GetStat_Level(int32 level)
{
	FString rowName = "Level_" + FString::FromInt(level);
	auto row = _statTable->FindRow<FCharacterStatData>(*rowName, TEXT(""));
	return *row;
}
