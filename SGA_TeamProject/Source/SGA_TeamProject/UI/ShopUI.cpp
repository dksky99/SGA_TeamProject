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
			button->OnClicked.AddDynamic(this, &UShopUI::SetShopData);
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
			button->OnClicked.AddDynamic(this, &UShopUI::SetInvenData);
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
		auto invenItem = inven->GetItemSlot_Index(i);
		SetInvenSlot(i, invenItem);

		auto shopItem = shop->GetItemSlot_Index(i);
		SetShopSlot(i, shopItem);
	}
}


void UShopUI::SetShopSlot(int32 index, FItemSlotData item)
{
	SetSlot(_shopButtons, _shopImages, index, item);
}

void UShopUI::SetInvenSlot(int32 index, FItemSlotData item)
{
	SetSlot(_invenButtons, _invenImages, index, item);
}

void UShopUI::SetSlot(TArray<class UInvenButton*> buttons, TArray<UImage*>& images, int32 index, FItemSlotData item)
{
	if (item.count == 0)
	{
		//buttons[index]->Count->SetText(FText::FromString(TEXT("")));
		images[index]->SetBrushFromTexture(_defaultTexture);
	}
	else
	{
		FString count = FString::Printf(TEXT("%d"), item.count);
		//buttons[index]->Count->SetText(FText::FromString(count));

		UTexture2D* itemIcon = item.itemData.icon.LoadSynchronous();
		images[index]->SetBrushFromTexture(itemIcon);
	}
}

void UShopUI::SetShopData()
{
	if (_getShopItemData.IsBound() == false)
		return;

	auto data = _getShopItemData.Execute(_curShopIndex);

	SetData(ShopItemData, ShopItemImage, data);
}

void UShopUI::SetInvenData()
{
	if (_getInvenItemData.IsBound() == false)
		return;

	auto data = _getInvenItemData.Execute(_curInvenIndex);

	SetData(InvenItemData, InvenItemImage, data);
}

void UShopUI::SetData(UTextBlock* textBlock, UImage* imageBlock, FItemData data)
{
	if (data.id == -1)
	{
		textBlock->SetText(FText::FromString(TEXT("")));
		imageBlock->SetBrushFromTexture(_defaultTexture);
	}
	else
	{
		textBlock->SetText(FText::FromString(TEXT("ItemType : POTION \nItemID : 1")));

		UTexture2D* itemIcon = data.icon.LoadSynchronous();
		imageBlock->SetBrushFromTexture(itemIcon);
	}
}
