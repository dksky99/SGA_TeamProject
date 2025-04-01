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
			slot->Button->OnClicked.AddDynamic(Armor, &UItemSlotUI::SetIndex);
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
	
	return true;
}

void UEquipUI::ResetEquip()
{
	for (auto slot : _equipSlots)
	{
		slot->SetDefault();
	}
}

void UEquipUI::UpdateEquip(AItemBase* item)
{
	auto data = item->GetData();
	if (data.equipSlot == EquipSlot::WEAPON)
	{
		Weapon->SetItem(data);
	}

	if (data.equipSlot == EquipSlot::ARMOR)
	{
		Armor->SetItem(data);
	}
}
