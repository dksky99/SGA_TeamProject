


//Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "../Character/InvenComponent.h"

#include "ItemSlotUI.h"

bool UShopUI::Initialize()
{
	Super::Initialize();

	// Shop slot
	auto array = ShopGrid->GetAllChildren();

	int32 index = 0;
	for (auto widget : array)
	{
		auto slot = Cast<UItemSlotUI>(widget);
		if (slot)
		{
			slot->Button->OnClicked.AddDynamic(slot, &UItemSlotUI::SetShop_ShopIndex);
			slot->Button->OnClicked.AddDynamic(this, &UShopUI::SetShopData);
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
			slot->Button->OnClicked.AddDynamic(this, &UShopUI::SetInvenData);
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

	SetShopData();
	SetInvenData();

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
		slots[index]->SetItem(item.count, item.itemData.icon);
	}
}

void UShopUI::SetShopData()
{
	if (_getShopItemData.IsBound() == false)
		return;

	auto data = _getShopItemData.Execute(_curShopIndex);

	SetData(ShopItemData, ShopItemImage, ShopPrice, data);
}

void UShopUI::SetInvenData()
{
	if (_getInvenItemData.IsBound() == false)
		return;

	auto data = _getInvenItemData.Execute(_curInvenIndex);

	SetData(InvenItemData, InvenItemImage, InvenPrice, data);
}

void UShopUI::SetData(UTextBlock* itemData, UImage* itemImage, UTextBlock* itemPrice, FItemData data)
{
	if (data.id == -1)
	{
		itemData->SetText(FText::FromString(TEXT("")));
		itemImage->SetBrushFromTexture(_defaultTexture);
		itemPrice->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		UEnum* enumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("ItemType"), true);
		FString itemType = enumType->GetNameStringByIndex((int32)data.type);
		FString itemName = data.name.ToString();

		FString text = FString::Printf(TEXT("%s\nItemType : %s\nItemID : %d"), *itemName, *itemType, data.id);
		itemData->SetText(FText::FromString(text));

		UTexture2D* itemIcon = data.icon.LoadSynchronous();
		itemImage->SetBrushFromTexture(itemIcon);

		int32 price = data.price;
		if (itemPrice == InvenPrice)
			price /= 2;
		text = FString::Printf(TEXT("%d"), price);
		itemPrice->SetText(FText::FromString(text));
	}
}
