// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Item/Item.h"
#include "ShopUI.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_RetVal_OneParam(FCItemInfo, FGetInvenItemInfo, int32);
DECLARE_DELEGATE_RetVal_OneParam(FCItemInfo, FGetShopItemInfo, int32);

UCLASS()
class SGA_TEAMPROJECT_API UShopUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void UpdateShop(class UInvenComponent* inven, class UInvenComponent* shop);

	void SetShopSlot(int32 index, FCItemInfo info);
	void SetInvenSlot(int32 index, FCItemInfo info);
	void SetSlot(TArray<class UImage*>& imageArray, int32 index, FCItemInfo info);

	UFUNCTION()
	void SetShopInfo();
	UFUNCTION()
	void SetInvenInfo();
	void SetInfo(class UTextBlock* textBlock, class UImage* imageBlock, FCItemInfo info);


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

	FGetInvenItemInfo _getInvenItemInfo;
	FGetShopItemInfo _getShopItemInfo;

	float _curInvenIndex = -1;
	float _curShopIndex = -1;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _potionTexture;
};
