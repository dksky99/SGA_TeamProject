// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Item/Item.h"
#include "ShopUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UShopUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void UpdateShop(class UInvenComponent* inven, class UInvenComponent* shop);

	void SetShopItem_Index(int32 index, FCItemInfo info);
	void SetInvenItem_Index(int32 index, FCItemInfo info);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* ShopGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* InvenGrid;

	// 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Buy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Sell;

	// 슬롯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> _shopImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> _invenImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UInvenButton*> _shopButtons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UInvenButton*> _invenButtons;


	// 아이템 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ShopItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InvenItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ShopItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* InvenItemImage;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _potionTexture;
};
