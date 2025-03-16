// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "InvenButton.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UInvenButton : public UButton
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	// 플레이어 인벤토리
	void SetInvenIndex();

	// 상점
	UFUNCTION()
	void SetShop_ShopIndex();
	UFUNCTION()
	void SetShop_InvenIndex();

	class UUserWidget* _widget;

	int32 _buttonIndex;
};
