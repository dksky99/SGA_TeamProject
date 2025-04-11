// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotUI.h"

#include "InvenUI.h"
#include "ShopUI.h"
#include "EquipUI.h"
#include "ItemInfoUI.h"

#include "../Character/InvenComponent.h"
#include "../Item/ItemManager.h"

void UItemSlotUI::SetDefault()
{
	_itemSlotCount->SetText(FText::FromString(TEXT("")));
	_itemSlotImage->SetBrushFromTexture(_defaultTexture);
	SetToolTip(nullptr);
}

void UItemSlotUI::SetItem(const FItemSlotData& item)
{
	FString text = FString::Printf(TEXT("%d"), item.count);
	_itemSlotCount->SetText(FText::FromString(text));

	SetItem(item.itemData);
}

void UItemSlotUI::SetItem(const FItemData& item)
{
	UTexture2D* image = ITEM_M->GetIcon(item.id);
	if (image)
		_itemSlotImage->SetBrushFromTexture(image);

	if (_widget->IsA<UInvenUI>() || _widget->IsA<UEquipUI>())
	{
		_toolTip->SetItemInfo(item);
		SetToolTip(_toolTip);
	}
}

void UItemSlotUI::SetIndex()
{
	if (_widget == nullptr)
		return;

	//auto widget = Cast<UInvenUI>(_widget);
	if (auto widget = Cast<UInvenUI>(_widget))
	{
		widget->_curIndex = _buttonIndex;
		return;
	}

	//widget = Cast<UEquipUI>(_widget);
	if (auto widget = Cast<UEquipUI>(_widget))
	{
		widget->_curIndex = _buttonIndex;
		return;
	}
}

void UItemSlotUI::SetShop_ShopIndex()
{
	if (_widget == nullptr)
		return;

	auto widget = Cast<UShopUI>(_widget);
	if (widget)
	{
		widget->_curShopIndex = _buttonIndex;
		return;
	}
}

void UItemSlotUI::SetShop_InvenIndex()
{
	if (_widget == nullptr)
		return;

	auto widget = Cast<UShopUI>(_widget);
	if (widget)
	{
		widget->_curInvenIndex = _buttonIndex;
		return;
	}
}
