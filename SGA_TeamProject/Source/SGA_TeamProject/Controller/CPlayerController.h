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


	class UInvenComponent* GetInvenComponent() { return _invenComponent; }

	class UPartyListUI* GetPartyListWidget() { return _partyListWidget; }

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* _inputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UInvenComponent* _invenComponent;

	// ÆÀ¿ø ¸®½ºÆ®
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _partyListClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	class UPartyListUI* _partyListWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camp", meta = (AllowPrivateAccess = "true"))
	class UTeamManager* _curCamp;

	int32 _curPlayerIndex = 0;
};
