// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "ItemSlotUI.h"
#include "../Character/InvenComponent.h"

bool UInvenUI::Initialize()
{
	Super::Initialize();

	auto array = Grid->GetAllChildren();

	int32 index = 0;
	for (auto widget : array)
	{
		auto slot = Cast<UItemSlotUI>(widget);
		if (slot)
		{
			slot->Button->OnClicked.AddDynamic(slot, &UItemSlotUI::SetInvenIndex);
			slot->_widget = this;
			slot->_buttonIndex = index;

			_itemSlots.Add(slot);
			index++;
		}
	}

	return true;
}

void UInvenUI::SetItem_Index(int32 index, const FItemSlotData& item)
{
	if (item.count == 0)
	{
		_itemSlots[index]->SetDefault();
	}
	else
	{
		_itemSlots[index]->SetItem(item.count, item.itemData.icon);
	}
}
