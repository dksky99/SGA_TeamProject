// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UItemSlotUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// TODO
	// 
	//UFUNCTION()
	//void SetInvenIndex();

	//// ªÛ¡°
	//UFUNCTION()
	//void SetShop_ShopIndex();
	//UFUNCTION()
	//void SetShop_InvenIndex();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UTextBlock* Count;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UButton* Button;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* Image;

	class UUserWidget* _widget;

	int32 _buttonIndex;
};
