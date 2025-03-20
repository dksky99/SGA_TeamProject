// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenComponent.h"

// Sets default values for this component's properties
UInvenComponent::UInvenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_items.SetNum(9);
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

FItemData UInvenComponent::GetItemData_Index(int32 index)
{
	if (index < 0 || index >= _items.Num())
		return FItemData();

	if (_items[index] == nullptr)
		return FItemData();

	return _items[index]->GetData();
}

AItem* UInvenComponent::GetItem_Index(int32 index)
{
	if (index < 0 || index >= _items.Num())
		return nullptr;

	if (_items[index] == nullptr)
		return nullptr;

	return _items[index];
}

void UInvenComponent::AddItem(AItem* item)
{
	auto target = _items.IndexOfByPredicate([](AItem* item)->bool
		{
			return item == nullptr;
		});

	if (target == INDEX_NONE)
		return;

	_items[target] = item;

	if (_itemChangeEvent.IsBound())
		_itemChangeEvent.Broadcast(target, item->GetData());
}

AItem* UInvenComponent::RemoveItem()
{
	auto target = _items.FindLastByPredicate([](AItem* item)->bool
		{
			return item != nullptr;
		});

	if (target == INDEX_NONE)
		return nullptr;

	AItem* dropItem = _items[target];
	_items[target] = nullptr;

	if (_itemChangeEvent.IsBound())
		_itemChangeEvent.Broadcast(target, FItemData());

	return dropItem;
}

AItem* UInvenComponent::RemoveItem(int32 index)
{
	if (index >= _items.Num() || index < 0)
		return nullptr;

	if (_items[index] == nullptr)
		return nullptr;

	AItem* dropItem = _items[index];
	_items[index] = nullptr;

	if (_itemChangeEvent.IsBound())
		_itemChangeEvent.Broadcast(index, FItemData());

	return dropItem;
}

bool UInvenComponent::IsFull()
{
	auto target = _items.IndexOfByPredicate([](AItem* item)->bool
		{
			return item == nullptr;
		});

	return target == INDEX_NONE;
}

