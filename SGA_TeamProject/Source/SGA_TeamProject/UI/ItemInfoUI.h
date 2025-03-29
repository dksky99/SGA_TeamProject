// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UItemInfoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetDefault();
	void SetItemInfo(struct FItemData data);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;
};
