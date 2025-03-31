// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Item/ItemDataTable.h"
#include "EquipUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UEquipUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void ResetEquip();
	void UpdateEquip(class AItemBase* item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UItemSlotUI* Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UItemSlotUI* Weapon;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UItemSlotUI*> _equipSlots;

	int32 _curIndex = -1;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToolTip", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _toolTipClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;
};