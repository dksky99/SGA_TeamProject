// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUI.h"

#include "Components/UniformGridPanel.h"
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
			button->OnClicked.AddDynamic(button, &UInvenButton::SetButtonIndex);
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
			button->OnClicked.AddDynamic(button, &UInvenButton::SetButtonIndex);
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
		SetInvenItem_Index(i, invenItem);

		auto shopItem = shop->GetItemInfo_Index(i);
		SetShopItem_Index(i, shopItem);
	}
}


void UShopUI::SetShopItem_Index(int32 index, FCItemInfo info)
{
	if (info.itemId == -1 && info.type == ItemType::NONE)
	{
		_shopImages[index]->SetBrushFromTexture(_defaultTexture);
	}

	if (info.itemId == 1 && info.type == ItemType::POTION)
	{
		_shopImages[index]->SetBrushFromTexture(_potionTexture);
	}
}

void UShopUI::SetInvenItem_Index(int32 index, FCItemInfo info)
{
	if (info.itemId == -1 && info.type == ItemType::NONE)
	{
		_invenImages[index]->SetBrushFromTexture(_defaultTexture);
	}

	if (info.itemId == 1 && info.type == ItemType::POTION)
	{
		_invenImages[index]->SetBrushFromTexture(_potionTexture);
	}
}
