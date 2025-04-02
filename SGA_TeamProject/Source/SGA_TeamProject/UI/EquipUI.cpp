// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "../Character/PlayerCharacter.h"
#include "../Item/ItemBase.h"

#include "ItemSlotUI.h"
#include "ItemInfoUI.h"

bool UEquipUI::Initialize()
{
	Super::Initialize();

	auto array = Grid->GetAllChildren();

	int32 index = 0;
	for (auto widget : array)
	{
		auto slot = Cast<UItemSlotUI>(widget);
		if (slot)
		{
			slot->Button->OnClicked.AddDynamic(slot, &UItemSlotUI::SetIndex);
			slot->_widget = this;
			slot->_buttonIndex = index;

			if (_toolTipClass)
			{
				auto toolTip = CreateWidget<UItemInfoUI>(GetWorld(), _toolTipClass);
				slot->_toolTip = toolTip;
			}

			_equipSlots.Add(slot);
			index++;
		}
	}
	
	_equipItems.SetNum(index);

	return true;
}

void UEquipUI::ResetEquip()
{
	for (auto slot : _equipSlots)
	{
		slot->SetDefault();
	}
}

void UEquipUI::UpdateEquip(AItemBase* item, bool _isUnequip)
{
	auto data = item->GetData();
	int32 index = static_cast<int32>(data.equipSlot);

	if (index == 0)
		return;

	// 장비 해제일 경우
	if (_isUnequip == true)
	{
		_equipSlots[index - 1]->SetDefault();
		_equipItems[index - 1] = nullptr;
	}
	
	// 장비 장착일 경우
	else
	{
		_equipSlots[index - 1]->SetItem(data);
		_equipItems[index - 1] = item;
	}
}
