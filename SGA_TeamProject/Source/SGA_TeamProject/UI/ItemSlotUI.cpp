// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotUI.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "InvenUI.h"
#include "ShopUI.h"

void UItemSlotUI::SetDefault()
{
	Count->SetText(FText::FromString(TEXT("")));
	Image->SetBrushFromTexture(_defaultTexture);
}

void UItemSlotUI::SetItem(int32 count, TSoftObjectPtr<UTexture2D> itemIcon)
{
	FString text = FString::Printf(TEXT("%d"), count);
	Count->SetText(FText::FromString(text));

	UTexture2D* image = itemIcon.LoadSynchronous();
	Image->SetBrushFromTexture(image);
}

void UItemSlotUI::SetInvenIndex()
{
	if (_widget == nullptr)
		return;

	auto widget = Cast<UInvenUI>(_widget);
	if (widget)
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
