// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "EquipItem.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AEquipItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void UseItem(class APlayerCharacter* player) override;
	void RemoveItem(class APlayerCharacter* player);
};
