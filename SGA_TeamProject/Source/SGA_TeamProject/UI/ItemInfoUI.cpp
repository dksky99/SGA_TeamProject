// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoUI.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Item/ItemBase.h"

void UItemInfoUI::SetDefault()
{
	if (!Text) return;
	Text->SetText(FText::FromString(TEXT("")));

	if (!Image) return;
	Image->SetBrushFromTexture(_defaultTexture);
}

void UItemInfoUI::SetItemInfo(const FItemData& data)
{
	UEnum* enumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("ItemType"), true);
	FString itemType = enumType->GetNameStringByIndex((int32)data.type);
	FString itemName = data.name.ToString();
	FString text = FString::Printf(TEXT("%s\nItemType : %s\nItemID : %d"), *itemName, *itemType, data.id);

	if (data.type == ItemType::EQUIPMENT)
	{
		if (data.hp != 0)
			text += FString::Printf(TEXT("\nHP : +%d"), data.hp);
		if (data.atk != 0)
			text += FString::Printf(TEXT("\nATK : +%d"), data.atk);
		if (data.speed != 0.0f)
			text += FString::Printf(TEXT("\nSpeed : +%f"), data.speed);
	}
	
	if (!Text) return;
	Text->SetText(FText::FromString(text));

	UTexture2D* itemIcon = data.icon.LoadSynchronous();
	if (!Image || itemIcon) return;
	Image->SetBrushFromTexture(itemIcon);
}
