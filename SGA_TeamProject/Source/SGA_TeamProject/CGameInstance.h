// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance();

	virtual void Init() override;

	struct FCharacterStatData GetStat_Level(int32 level);

	struct FItemData GetItemData_ID(int32 id);

	class AItemManager* ItemManager() { return _itemManager; }

private:
	// Stat
	UPROPERTY()
	class UDataTable* _statTable;

	// Item
	UPROPERTY()
	class UDataTable* _itemTable;

	UPROPERTY()
	class AItemManager* _itemManager;
};
