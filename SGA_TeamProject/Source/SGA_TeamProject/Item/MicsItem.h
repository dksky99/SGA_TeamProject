// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "MicsItem.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AMicsItem : public AItemBase
{
	GENERATED_BODY()

public:
	AMicsItem() {};
	
	virtual void UseItem(class APlayerCharacter* player) override {};
};
