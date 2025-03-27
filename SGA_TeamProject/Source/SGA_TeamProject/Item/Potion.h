// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API APotion : public AItem
{
	GENERATED_BODY()
	
public:
	APotion();

	virtual void UseItem(class APlayerCharacter* player) override;
};
