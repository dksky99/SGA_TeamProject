// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Character/InvenComponent.h"

#include "InvenButton.h"

bool UShopUI::Initialize()
{
	Super::Initialize();

	// Shop slot
	auto array = ShopGrid->GetAllChildren();

	int32 index = 0;
	for (auto widget : array)
	{
		auto button = Cast<UInvenButton>(widget);
		if (button)
		{
			button->OnClicked.AddDynamic(button, &UInvenButton::SetShop_ShopIndex);
			button->OnClicked.AddDynamic(this, &UShopUI::SetShopInfo);
			button->_widget = this;
			button->_buttonIndex = index;

			_shopButtons.Add(button);
			index++;
		}

		auto image = Cast<UImage>(button->GetChildAt(0));
		if (image)
		{
			_shopImages.Add(image);
		}
	}

	// inven slot
	array = InvenGrid->GetAllChildren();

	index = 0;
	for (auto widget : array)
	{
		auto button = Cast<UInvenButton>(widget);
		if (button)
		{
			button->OnClicked.AddDynamic(button, &UInvenButton::SetShop_InvenIndex);
			button->OnClicked.AddDynamic(this, &UShopUI::SetInvenInfo);
			button->_widget = this;
			button->_buttonIndex = index;

			_invenButtons.Add(button);
			index++;
		}

		auto image = Cast<UImage>(button->GetChildAt(0));
		if (image)
		{
			_invenImages.Add(image);
		}
	}

	return true;
}

void UShopUI::UpdateShop(UInvenComponent* inven, UInvenComponent* shop)
{
	for (int i = 0; i < 9; i++)
	{
		auto invenItem = inven->GetItemInfo_Index(i);
		SetInvenSlot(i, invenItem);

		auto shopItem = shop->GetItemInfo_Index(i);
		SetShopSlot(i, shopItem);
	}
}


void UShopUI::SetShopSlot(int32 index, FCItemInfo info)
{
	SetSlot(_shopImages, index, info);
}

void UShopUI::SetInvenSlot(int32 index, FCItemInfo info)
{
	SetSlot(_invenImages, index, info);
}

void UShopUI::SetSlot(TArray<UImage*>& imageArray, int32 index, FCItemInfo info)
{
	if (info.itemId == -1 && info.type == ItemType::NONE)
	{
		imageArray[index]->SetBrushFromTexture(_defaultTexture);
	}
	else if (info.itemId == 1 && info.type == ItemType::POTION)
	{
		imageArray[index]->SetBrushFromTexture(_potionTexture);
	}
}

void UShopUI::SetShopInfo()
{
	if (_getShopItemInfo.IsBound() == false)
		return;

	auto info = _getShopItemInfo.Execute(_curShopIndex);

	SetInfo(ShopItemInfo, ShopItemImage, info);
}

void UShopUI::SetInvenInfo()
{
	if (_getInvenItemInfo.IsBound() == false)
		return;

	auto info = _getInvenItemInfo.Execute(_curInvenIndex);

	SetInfo(InvenItemInfo, InvenItemImage, info);
}

void UShopUI::SetInfo(UTextBlock* textBlock, UImage* imageBlock, FCItemInfo info)
{
	if (info.itemId == -1 && info.type == ItemType::NONE)
	{
		textBlock->SetText(FText::FromString(TEXT("ItemType : NONE \nItemID : -1")));
		imageBlock->SetBrushFromTexture(_defaultTexture);
	}
	else if (info.itemId == 1 && info.type == ItemType::POTION)
	{
		textBlock->SetText(FText::FromString(TEXT("ItemType : POTION \nItemID : 1")));
		imageBlock->SetBrushFromTexture(_potionTexture);
	}
}
