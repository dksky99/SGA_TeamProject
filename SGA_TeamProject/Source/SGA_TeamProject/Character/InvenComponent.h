// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/itemBase.h"
#include "../Item/ItemDataTable.h"
#include "InvenComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FItemChangeEvent, int32, const FItemSlotData&);
DECLARE_MULTICAST_DELEGATE_OneParam(FGoldChangeEvent, int32);

USTRUCT(BlueprintType)
struct FItemSlotData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData itemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 count = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAMPROJECT_API UInvenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInvenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FItemSlotData GetItemSlot_Index(int32 index);
	FItemData GetItemData_Index(int32 index);

	void AddItem(FItemData itemdata, int32 count = 1);
	FItemData RemoveItem();
	FItemData RemoveItem(int32 index);

	int32 GetGold() { return _gold; }
	void SetGold(int32 gold);

	bool IsFull();

	FItemChangeEvent _itemChangeEvent;
	FGoldChangeEvent _goldChangeEvent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TArray<FItemSlotData> _items;

	UPROPERTY(VisibleAnywhere)
	int32 _gold = 0;
};
