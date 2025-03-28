// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.h"
#include "ItemManager.generated.h"

USTRUCT()
struct FCItems
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AItemBase*> _items;
};

UCLASS()
class SGA_TEAMPROJECT_API AItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AItemBase* GetItem(int32 id);
	void SpawnItem(int32 id, FVector pos);

private:
	UPROPERTY(VisibleAnywhere)
	TMap<int32, FCItems> _itemPool;

	UPROPERTY(EditAnywhere)
	int32 itemIDCount = 3; // 아이템 종류 수 (아이디 개수)

	UPROPERTY(EditAnywhere)
	int32 itemPoolCount = 10; // 각 종류당 풀 개수
};
