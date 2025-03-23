// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Item/Item.h"
#include "InvenUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UInvenUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetItem_Index(int32 index, const struct FItemSlotData& item);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Drop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UItemSlotUI*> _itemSlots;

	int32 _curIndex = -1;
};
