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

	if (ITEM_T)
	{
		TArray<FItemData*> allRows;
		ITEM_T->GetAllRows(TEXT(""), allRows);

		for (auto row : allRows)
		{
			if (!row->itemClass)
				continue;

			_itemPool.Add(row->id);
			
			for (int i = 0; i < itemPoolCount; i++)
			{
				auto item = GetWorld()->SpawnActor<AItemBase>(row->itemClass, FVector::ZeroVector, FRotator::ZeroRotator);
				item->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
				item->SetData(*row);
				item->Deactivate();

				_itemPool[row->id]._items.Add(item);
			}			
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
		UE_LOG(LogTemp, Error, TEXT("Item Spawn"));
	}
}

