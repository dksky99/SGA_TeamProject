// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "InvenButton.h"
#include "../Character/InvenComponent.h"

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
			button->OnClicked.AddDynamic(button, &UInvenButton::SetInvenIndex);
			button->_widget = this;
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

void UInvenUI::SetItem_Index(int32 index, const FItemSlotData& item)
{
	if (item.count == 0)
	{
		//_buttons[index]->Count->SetText(FText::FromString(TEXT("")));
		_slotImages[index]->SetBrushFromTexture(_defaultTexture);
	}
	else
	{
		FString count = FString::Printf(TEXT("%d"), item.count);
		//_buttons[index]->Count->SetText(FText::FromString(count));

		UTexture2D* itemIcon = item.itemData.icon.LoadSynchronous();
		_slotImages[index]->SetBrushFromTexture(itemIcon);
	}
}
