// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeadEvent);

UCLASS()
class SGA_TEAMPROJECT_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

	virtual void BeginPlay()override;

	void ShowUI();
	void HideUI();

	UFUNCTION()
	void CharacterChange();

	class ACharacterBase* FindNewCharacterForPlayer();

	class UInvenComponent* GetInvenComponent() { return _invenComponent; }

	FPlayerDeadEvent _playerDeadEvent;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* _inputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UInvenComponent* _invenComponent;
};
