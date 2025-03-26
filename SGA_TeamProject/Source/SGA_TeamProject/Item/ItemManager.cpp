// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

#include "../CGameInstance.h"
#include "ItemDataTable.h"

// Sets default values
AItemManager::AItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();

	auto gameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());
	for (int32 i = 1; i <= itemIDCount; i++)
	{
		int32 id = i;
		_itemPool.Add(id);
		auto itemData = gameInstance->GetItemData_ID(id);
		auto itemClass = itemData.itemClass;

		for (int j = 0; j < itemPoolCount; j++)
		{
			auto item = GetWorld()->SpawnActor<AItemBase>(itemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			item->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			item->SetData(itemData);
			item->Deactivate();
			
			_itemPool[id]._items.Add(item);
		}
	}
}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AItemBase* AItemManager::GetItem(int32 id)
{
	auto items = _itemPool.Find(id);
	if (!items)
		return nullptr;

	auto iter = items->_items.FindByPredicate([](AItemBase* item)->bool
		{
			return !item->IsActive();
		});

	if (iter)
	{
		return *iter;
	}
	
	return nullptr;
}

void AItemManager::SpawnItem(int32 id, FVector pos)
{
	auto item = GetItem(id);

	if (item)
	{
		item->Activate();
		item->SetActorLocation(pos);
	}
}

