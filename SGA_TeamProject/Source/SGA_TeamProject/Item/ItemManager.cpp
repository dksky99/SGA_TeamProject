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
		_itemTable.Add(id);
		auto itemData = gameInstance->GetItemData_ID(id);
		auto itemClass = itemData.itemClass;

		for (int j = 0; j < itemPoolCount; j++)
		{
			auto item = GetWorld()->SpawnActor<AItem>(itemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			item->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			item->Deactivate();
			
			_itemTable[id]._items.Add(item);
		}
	}
}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemManager::SpawnItem(int32 key, FVector pos)
{
	auto items = _itemTable.Find(key);
	if (!items)
		return;

	auto iter = items->_items.FindByPredicate([](AItem* item)->bool
		{
			return !item->IsActive();
		});

	if (iter)
	{
		(*iter)->Activate();
		(*iter)->SetActorLocation(pos);
	}
}

