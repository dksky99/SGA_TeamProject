// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoUI.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../CGameInstance.h"
#include "../Item/ItemBase.h"
#include "../Item/ItemManager.h"

void UItemInfoUI::SetDefault()
{
	if (!_itemInfoText) return;
	_itemInfoText->SetText(FText::FromString(TEXT("")));

	if (!_itemInfoImage) return;
	_itemInfoImage->SetBrushFromTexture(_defaultTexture);
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
	
	if(_itemInfoText->IsValidLowLevel())
		_itemInfoText->SetText(FText::FromString(text));
	else
		UE_LOG(LogTemp, Error, TEXT("_itemInfoText Error"));

	auto instance = Cast<UCGameInstance>(GetGameInstance());
	if (instance)
	{
		if (_itemManager == nullptr)
		{
			_itemManager = instance->ItemManager();
		}
		
		auto image = _itemManager->GetIcon(data.id);
		if (image)
			_itemInfoImage->SetBrushFromTexture(image);
		else
		{
			UE_LOG(LogTemp, Error, TEXT("image Error"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Instance Error"));
	}
}
