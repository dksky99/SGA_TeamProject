// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/Item.h"
#include "InvenComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FItemChangeEvent, int32, FCItemInfo);

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

	FCItemInfo GetItemInfo_Index(int32 index);
	AItem* GetItem_Index(int32 index);

	void AddItem(AItem* item);
	AItem* RemoveItem();
	AItem* RemoveItem(int32 index);

	bool IsFull();

	FItemChangeEvent _itemChangeEvent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TArray<AItem*> _items;
};
