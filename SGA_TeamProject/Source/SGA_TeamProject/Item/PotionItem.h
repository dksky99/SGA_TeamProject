// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API APotionItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	APotionItem();

	virtual void UseItem(class APlayerCharacter* player) override;
};
