// Fill out your copyright notice in the Descr// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"
#include "ItemDataTable.generated.h"

UENUM()
enum class ItemType
{
	NONE,
	POTION,
	EQUIPMENT
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 id = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ItemType type = ItemType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AItem> itemClass;
};

UCLASS()
class SGA_TEAMPROJECT_API UItemDataTable : public UObject
{
	GENERATED_BODY()
	
};
