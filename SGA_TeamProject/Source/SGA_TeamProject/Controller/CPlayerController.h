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
#define EQUIP_UI Cast<ACPlayerController>(GetWorld()->GetFirstPlayerController())->GetEquipWidget()

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
	class UEquipUI* GetEquipWidget() { return _equipWidget; }

	UFUNCTION()
	void DropItemByClick();
	//TODO
	// 장착 리스트를 인벤 컴포넌트에서 구현(캐릭터에 구현 시 캐릭터 사망과 동시에 아이템에 접근할 방법이 없어짐)
	// 인벤 컴포넌트에서 TMap<ACharacterBase*, TMap<EquipSlot, AItem*>> _characterEquipMap; 를 만든다
	// 컨트롤러에서 아이템을 장착하면 인벤 컴포넌트에서 캐릭터의 아이템 장착 함수를 불러온다
	// 아이템 장착해제 구현 (인벤토리가 꽉 차있으면 아무동작을 하지 않는다)
	// 아이템 교체는 장착해제전 아이템을 임시공간에 저장 후 인벤토리 칸을 비워준 후 장착
	UFUNCTION()
	void UseItemByClick();

	UFUNCTION()
	void UnequipItemByClick();

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

	// 장비
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _equipWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UEquipUI* _equipWidget;

	// 팀원 리스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _partyListClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PartyList", meta = (AllowPrivateAccess = "true"))
	class UPartyListUI* _partyListWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camp", meta = (AllowPrivateAccess = "true"))
	class UTeamManager* _curCamp;

	int32 _curPlayerIndex = 0;
};
