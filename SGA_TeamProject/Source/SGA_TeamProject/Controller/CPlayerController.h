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
	ACPlayerController();

	virtual void BeginPlay()override;

	virtual void OnPossess(APawn* pawn) override;
	virtual void OnUnPossess() override;


	void ShowUI();
	void HideUI();

	UFUNCTION()
	void CharacterChange();

	class ACharacterBase* FindNewCharacterForPlayer();

	class UInvenComponent* GetInvenComponent() { return _invenComponent; }

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* _inputMappingContext;




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UInvenComponent* _invenComponent;
};
