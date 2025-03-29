


//Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "../Character/InvenComponent.h"

#include "ItemSlotUI.h"
#include "ItemInfoUI.h"

bool UShopUI::Initialize()
{
	Super::Initialize();

	//Shop slot
	auto array = ShopGrid->GetAllChildren();

	int32 index = 0;
	for (auto widget : array)
	{
		auto slot = Cast<UItemSlotUI>(widget);
		if (slot)
		{
			slot->Button->OnClicked.AddDynamic(slot, &UItemSlotUI::SetShop_ShopIndex);
			slot->Button->OnClicked.AddDynamic(this, &UShopUI::SetShopItemInfo);
			slot->_widget = this;
			slot->_buttonIndex = index;

			_shopSlots.Add(slot);
			index++;
		}
	}

	// Inven slot
	array = InvenGrid->GetAllChildren();

	index = 0;
	for (auto widget : array)
	{
		auto slot = Cast<UItemSlotUI>(widget);
		if (slot)
		{
			slot->Button->OnClicked.AddDynamic(slot, &UItemSlotUI::SetShop_InvenIndex);
			slot->Button->OnClicked.AddDynamic(this, &UShopUI::SetInvenItemInfo);
			slot->_widget = this;
			slot->_buttonIndex = index;

			_invenSlots.Add(slot);
			index++;
		}
	}

	return true;
}

void UShopUI::ResetUI(UInvenComponent* inven, UInvenComponent* shop)
{
	_curShopIndex = -1;
	_curInvenIndex = -1;

	UpdateShop(inven, shop);
}

void UShopUI::UpdateShop(UInvenComponent* inven, UInvenComponent* shop)
{
	for (int i = 0; i < 9; i++)
	{
		auto invenItem = inven->GetItemSlot_Index(i);
		SetInvenSlot(i, invenItem);

		auto shopItem = shop->GetItemSlot_Index(i);
		SetShopSlot(i, shopItem);
	}

	SetShopItemInfo();
	SetInvenItemInfo();

	int32 gold = inven->GetGold();
	FString text = FString::Printf(TEXT("%d"), gold);
	Gold->SetText(FText::FromString(text));
}


void UShopUI::SetShopSlot(int32 index, FItemSlotData item)
{
	SetSlot(_shopSlots, index, item);
}

void UShopUI::SetInvenSlot(int32 index, FItemSlotData item)
{
	SetSlot(_invenSlots, index, item);
}

void UShopUI::SetSlot(TArray<class UItemSlotUI*> slots, int32 index, FItemSlotData item)
{
	if (item.count == 0)
	{
		slots[index]->SetDefault();
	}
	else
	{
		slots[index]->SetItem(item);
	}
}

void UShopUI::SetShopItemInfo()
{
	if (_getShopItemData.IsBound() == false)
		return;

	auto data = _getShopItemData.Execute(_curShopIndex);

	SetItemInfo(ShopItemInfo, ShopPrice, data);
}

void UShopUI::SetInvenItemInfo()
{
	if (_getInvenItemData.IsBound() == false)
		return;

	auto data = _getInvenItemData.Execute(_curInvenIndex);

	SetItemInfo(InvenItemInfo, InvenPrice, data);
}

void UShopUI::SetItemInfo(UItemInfoUI* itemInfoUI, UTextBlock* itemPriceUI, FItemData data)
{
	if (data.id == -1)
	{
		itemInfoUI->SetDefault();
		itemPriceUI->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		itemInfoUI->SetItemInfo(data);

		int32 price = data.price;
		if (itemPriceUI == InvenPrice && data.type != ItemType::NONE)
			price /= 2;
		FString text = FString::Printf(TEXT("%d"), price);
		itemPriceUI->SetText(FText::FromString(text));
	}
}
