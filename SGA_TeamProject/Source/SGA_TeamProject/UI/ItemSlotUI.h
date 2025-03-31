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
	void SetDefault();
	void SetItem(const struct FItemSlotData& item);

	// 인벤토리
	UFUNCTION()
	void SetInvenIndex();

	// 상점
	UFUNCTION()
	void SetShop_ShopIndex();
	UFUNCTION()
	void SetShop_InvenIndex();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image;

	class UItemInfoUI* _toolTip;

	class UUserWidget* _widget;

	int32 _buttonIndex;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;
};
