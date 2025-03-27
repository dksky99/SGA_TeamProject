// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
#define INVEN_COMP Cast<ACPlayerController>(GetWorld()->GetFirstPlayerController())->GetInvenComponent()
#define INVEN_UI Cast<ACPlayerController>(GetWorld()->GetFirstPlayerController())->GetInvenWidget()

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
	class UInvenUI* GetInvenWidget() { return _invenWidget; }
	class UPartyListUI* GetPartyListWidget() { return _partyListWidget; }

	UFUNCTION()
	void DropItemByClick();
	UFUNCTION()
	void UseItemByClick();

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* _inputMappingContext;

	// 인벤토리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _invenWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UInvenUI* _invenWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UInvenComponent* _invenComponent;

	// 팀원 리스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _partyListClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	class UPartyListUI* _partyListWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camp", meta = (AllowPrivateAccess = "true"))
	class UTeamManager* _curCamp;

	int32 _curPlayerIndex = 0;
};
