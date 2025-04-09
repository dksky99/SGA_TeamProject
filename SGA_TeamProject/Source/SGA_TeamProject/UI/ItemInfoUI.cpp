// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoUI.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../CGameInstance.h"
#include "../Item/ItemBase.h"
#include "../Item/ItemManager.h"

void UItemInfoUI::SetDefault()
{
	if (!Text) return;
	Text->SetText(FText::FromString(TEXT("")));

	if (!Image) return;
	Image->SetBrushFromTexture(_defaultTexture);
}

void UItemInfoUI::SetItemInfo(const FItemData& data)
{
	FString itemName = data.name.ToString();
	FString text = FString::Printf(TEXT("%s"), *itemName);

	if (data.type == ItemType::EQUIPMENT)
	{
		UEnum* enumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("EquipSlot"), true);
		FString itemType = enumType->GetNameStringByIndex((int32)data.equipSlot);
		text += FString::Printf(TEXT("\n%s"), *itemType);

		if (data.hp != 0)
			text += FString::Printf(TEXT("\nHP : +%d"), data.hp);
		if (data.atk != 0)
			text += FString::Printf(TEXT("\nATK : +%d"), data.atk);
		if (data.speed != 0.0f)
			text += FString::Printf(TEXT("\nSpeed : +%f"), data.speed);
	}
	else
	{
		UEnum* enumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("ItemType"), true);
		FString itemType = enumType->GetNameStringByIndex((int32)data.type);
		text += FString::Printf(TEXT("\n%s"), *itemType);

		if (data.type == ItemType::POTION && data.heal != 0)
			text += FString::Printf(TEXT("\nHP : +%d"), data.heal);
	}
	
	Text->SetText(FText::FromString(text));

	UTexture2D* image = ITEM_M->GetIcon(data.id);
	if (image)
		Image->SetBrushFromTexture(image);
}
