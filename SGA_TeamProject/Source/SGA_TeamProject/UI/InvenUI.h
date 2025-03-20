// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Item/Item.h"
#include "InvenUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UInvenUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetItem_Index(int32 index, FItemData data);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Drop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> _slotImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UInvenButton*> _buttons;

	int32 _curIndex = -1;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _potionTexture;
};
