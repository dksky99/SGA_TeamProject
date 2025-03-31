// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenComponent.h"
#include "../Item/EquipItem.h"


// Sets default values for this component's properties
UInvenComponent::UInvenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_items.SetNum(9);
	_gold = 0;
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

void UInvenComponent::AddItem(FItemData item, int32 count, int32 index)
{
	// 인덱스가 주어지지 않았을 경우
	if (index == -1)
	{
		// 아이템이 장비가 아닐 경우 (장비는 겹치지 않게 저장)
		if (item.type != ItemType::EQUIPMENT)
		{
			index = _items.IndexOfByPredicate([item](const FItemSlotData& slot) -> bool
				{
					return slot.itemData.id == item.id;
				});
		}

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
	}

	_items[index].itemData = item;
	_items[index].count += count;
	
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

void UInvenComponent::SetGold(int32 gold)
{
	_gold = gold;

	if (_goldChangeEvent.IsBound())
		_goldChangeEvent.Broadcast(gold);
}

bool UInvenComponent::IsFull()
{
	auto index = _items.IndexOfByPredicate([](const FItemSlotData& slot)->bool
		{
			return slot.count == 0;
		});

	return index == INDEX_NONE;
}

void UInvenComponent::EquipItem(APlayerCharacter* player, AItemBase* item, int32 index)
{
	if (!player || !item) return;

	EquipSlot slot = item->GetData().equipSlot;
	if (slot == EquipSlot::NONE) return;

	if (_characterEquipMap.Contains(player))
	{
		if (_characterEquipMap[player].map.Contains(slot))
		{
			// 장착 슬롯에 아이템이 들어 있을 때
			UnequipItem(player, slot, index); 
		}
	}

	_characterEquipMap.FindOrAdd(player).map.Add(slot, item);

	if (_equipChangeEvent.IsBound())
		_equipChangeEvent.Broadcast(item);

	item->UseItem(player);
}

void UInvenComponent::UnequipItem(APlayerCharacter* player, EquipSlot slot, int32 index)
{
	if (!player || !_characterEquipMap.Contains(player)) return;

	// 장비 교체가 아닌 단순 해제이며, 인벤이 꽉 찼을 경우
	if (index == -1 && IsFull()) return;

	FEquipSlotMap& equipMap = _characterEquipMap[player];
	if (!equipMap.map.Contains(slot)) return;

	auto oldItem = Cast<AEquipItem>(equipMap.map[slot]);
	if (!oldItem) return;

	// 아이템 효과 제거
	oldItem->RemoveItem(player);
	// 인벤토리에 추가
	AddItem(oldItem->GetData(), 1, index);
	// 장착 목록에서 제거
	equipMap.map.Remove(slot);
}

void UInvenComponent::CharacterChange(APlayerCharacter* player)
{
	auto equipMap = _characterEquipMap.Find(player);
	if (!equipMap)
		return;

	for (const auto& equip : equipMap->map)
	{
		auto item = equip.Value;

		if (item && _equipChangeEvent.IsBound())
		{
			_equipChangeEvent.Broadcast(item);
		}
	}
}
