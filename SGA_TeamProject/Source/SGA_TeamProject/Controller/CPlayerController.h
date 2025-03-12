// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay()override;

	void ShowUI();
	void HideUI();

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* _inputMappingContext;

};
