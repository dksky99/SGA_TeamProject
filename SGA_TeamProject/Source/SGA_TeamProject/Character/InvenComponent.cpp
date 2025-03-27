// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenComponent.h"


// Sets default values for this component's properties
UInvenComponent::UInvenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_items.SetNum(9);
	_money = 0;
}


// Called when the game starts
void UInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInvenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemSlotData UInvenComponent::GetItemSlot_Index(int32 index)
{
	if (index < 0 || index >= _items.Num())
		return FItemSlotData();

	if (_items[index].count == 0)
		return FItemSlotData();

	return _items[index];
}

FItemData UInvenComponent::GetItemData_Index(int32 index)
{
	if (index < 0 || index >= _items.Num())
		return FItemData();

	if (_items[index].count == 0)
		return FItemData();

	return _items[index].itemData;
}

void UInvenComponent::AddItem(FItemData item)
{
	auto index = _items.IndexOfByPredicate([item](const FItemSlotData& slot) -> bool
		{
			return slot.itemData.id == item.id;
		});

	// 인벤에 해당 아이템 없을 경우
	if (index == INDEX_NONE)
	{
		index = _items.IndexOfByPredicate([](const FItemSlotData& slot) -> bool
			{
				return slot.count == 0;
			});
	}

	// 인벤에 빈 슬롯이 없을 경우
	if (index == INDEX_NONE)
		return;

	_items[index].itemData = item;
	_items[index].count++;
	

	if (_itemChangeEvent.IsBound())
		_itemChangeEvent.Broadcast(index, _items[index]);
}

FItemData UInvenComponent::RemoveItem()
{
	auto index = _items.FindLastByPredicate([](const FItemSlotData& slot)->bool
		{
			return slot.count != 0;
		});

	if (index == INDEX_NONE)
		return FItemData();

	FItemData dropItem = _items[index].itemData;

	_items[index].count--;
	if (_items[index].count == 0)
	{
		_items[index].itemData = FItemData();
	}

	if (_itemChangeEvent.IsBound())
		_itemChangeEvent.Broadcast(index, _items[index]);

	return dropItem;
}

FItemData UInvenComponent::RemoveItem(int32 index)
{
	if (index >= _items.Num() || index < 0)
		return FItemData();

	if (_items[index].count == 0)
		return FItemData();

	FItemData dropItem = _items[index].itemData;
	_items[index].count--;
	if (_items[index].count == 0)
	{
		_items[index].itemData = FItemData();
	}

	if (_itemChangeEvent.IsBound())
		_itemChangeEvent.Broadcast(index, _items[index]);

	return dropItem;
}

bool UInvenComponent::IsFull()
{
	auto index = _items.IndexOfByPredicate([](const FItemSlotData& slot)->bool
		{
			return slot.count == 0;
		});

	return index == INDEX_NONE;
}

void UInvenComponent::EquipItem(ACharacterBase* character, AItem* item)
{
	if (!character || !item) return;

	EquipSlot slot = item->GetData().equipSlot;
	if (slot == EquipSlot::NONE) return;

	if (_characterEquipMap.Contains(character))
	{
		if (_characterEquipMap[character].equipSlot.Contains(slot))
		{
			// 장착 슬롯에 아이템이 들어 있을 때
		}
	}

	_characterEquipMap.FindOrAdd(character).equipSlot.Add(slot, item);


}

