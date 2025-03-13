// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBar.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UHpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHpBarValue(float ratio);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;
};
