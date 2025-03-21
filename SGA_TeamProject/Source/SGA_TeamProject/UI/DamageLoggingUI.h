// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageLoggingUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UDamageLoggingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateList(TArray<TPair<class ACharacterBase*, int32>> damageArray);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* List;
};
