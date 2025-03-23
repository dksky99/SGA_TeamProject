// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Item/Item.h"
#include "ShopUI.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_RetVal_OneParam(FItemData, FGetInvenItemData, int32);
DECLARE_DELEGATE_RetVal_OneParam(FItemData, FGetShopItemData, int32);

UCLASS()
class SGA_TEAMPROJECT_API UShopUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void UpdateShop(class UInvenComponent* inven, class UInvenComponent* shop);

	// 상점, 인벤토리 칸 표시
	void SetShopSlot(int32 index, struct FItemSlotData data);
	void SetInvenSlot(int32 index, struct FItemSlotData data);
	void SetSlot(TArray<class UInvenButton*> buttons, TArray<class UImage*>& images, int32 index, FItemSlotData data);

	// 선택한 아이템 정보 표시
	UFUNCTION()
	void SetShopData();
	UFUNCTION()
	void SetInvenData();
	void SetData(class UTextBlock* textBlock, class UImage* imageBlock, FItemData data);


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
	class UTextBlock* ShopItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InvenItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ShopItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* InvenItemImage;

	FGetInvenItemData _getInvenItemData;
	FGetShopItemData _getShopItemData;

	float _curInvenIndex = -1;
	float _curShopIndex = -1;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _potionTexture;
};
