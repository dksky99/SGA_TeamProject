// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Image.h"

#include "InvenButton.h"

bool UInvenUI::Initialize()
{
	Super::Initialize();

	auto array = Grid->GetAllChildren();

	int32 index = 0;
	for (auto widget : array)
	{
		auto button = Cast<UInvenButton>(widget);
		if (button)
		{
			button->OnClicked.AddDynamic(button, &UInvenButton::SetButtonIndex);
			button->_invenUI = this;
			button->_buttonIndex = index;

			_buttons.Add(button);
			index++;
		}

		auto image = Cast<UImage>(button->GetChildAt(0));
		if (image)
		{
			_slotImages.Add(image);
		}
	}

	return true;
}

void UInvenUI::SetItem_Index(int32 index, FCItemInfo info)
{
	if (info.itemId == -1 && info.type == ItemType::NONE)
	{
		_slotImages[index]->SetBrushFromTexture(_defaultTexture);
	}

	if (info.itemId == 1 && info.type == ItemType::POTION)
	{
		_slotImages[index]->SetBrushFromTexture(_potionTexture);
	}
}
