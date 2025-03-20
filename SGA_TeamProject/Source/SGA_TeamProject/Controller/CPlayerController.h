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

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* pawn) override;
	virtual void OnUnPossess() override;


	void ShowUI();
	void HideUI();

	UFUNCTION()
	void CharacterChange();

	class ACharacterBase* FindNewCharacterForPlayer();

	class UInvenComponent* GetInvenComponent() { return _invenComponent; }

	class UUserWidget* GetPartyListWidget() { return _partyListWidget; }

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* _inputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UInvenComponent* _invenComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _partyListClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	class UUserWidget* _partyListWidget;
};
