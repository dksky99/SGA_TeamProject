// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"

#include "../Character/CharacterBase.h"
#include "../Character/PlayerCharacter.h"
#include "../Character/InvenComponent.h"

#include "../UI/PartyListUI.h"
#include "../UI/InvenUI.h"
#include "../TeamManager.h"

#include "../CGameInstance.h"
#include "../Item/ItemBase.h"
#include "../Item/ItemManager.h"

ACPlayerController::ACPlayerController()
{
	_invenComponent = CreateDefaultSubobject<UInvenComponent>(TEXT("InvenComponent"));
	_curCamp = CreateDefaultSubobject<UTeamManager>(TEXT("CampManager"));
}

void ACPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_partyListClass)
	{
		_partyListWidget = CreateWidget<UPartyListUI>(GetWorld(), _partyListClass);
		_curCamp->_teamChanged.AddUObject(_partyListWidget, &UPartyListUI::AddPartySlot);
		_curCamp->_characterChanged.AddUObject(_partyListWidget, &UPartyListUI::UpdateList);
	}

	if (_invenWidgetClass)
	{
		_invenWidget = CreateWidget<UInvenUI>(GetWorld(), _invenWidgetClass);
		_invenComponent->_itemChangeEvent.AddUObject(_invenWidget, &UInvenUI::SetItem_Index);
		_invenComponent->_goldChangeEvent.AddUObject(_invenWidget, &UInvenUI::SetGold);
		_invenWidget->Drop->OnClicked.AddDynamic(this, &ACPlayerController::DropItemByClick);
		_invenWidget->Use->OnClicked.AddDynamic(this, &ACPlayerController::UseItemByClick);
	}
}

void ACPlayerController::BeginPlay()
{
	//부모의 BeginPlay 호출. 상속구조의 이벤트는 부모의 이벤트를 호출해줘야함
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* subSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (subSystem)
	{
		subSystem->AddMappingContext(_inputMappingContext, 0);
	}

	if (_partyListWidget)
	{
		_partyListWidget->AddToViewport();
	}
}

void ACPlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);


}

void ACPlayerController::OnUnPossess()
{
	Super::OnUnPossess();


}

void ACPlayerController::ShowUI()
{

	bShowMouseCursor = true;
}

void ACPlayerController::HideUI()
{

	bShowMouseCursor = false;
}

void ACPlayerController::CharacterChange()
{
	UE_LOG(LogTemp, Warning, TEXT("CharacterChange : %d"), _curPlayerIndex);

	ACharacterBase* playerCharacter = Cast<ACharacterBase>(GetPawn());
	if (!playerCharacter) return;

	const TArray<ACharacterBase*>& teamMembers = _curCamp->GetTeamMembers();
	const int32 memberCount = teamMembers.Num();
	if (memberCount == 0) return;

	ACharacterBase* targetCharacter = nullptr;

	for (int32 i = 0; i < memberCount; i++)
	{
		int32 index = (_curPlayerIndex + i) % memberCount;
		ACharacterBase* candidate = teamMembers[index];

		if (candidate && candidate->IsAlive() && candidate != playerCharacter)
		{
			targetCharacter = candidate;
			_curPlayerIndex = (index + 1) % memberCount;
			break;
		}
	}

	// 살아있는 캐릭터가 없으면 종료
	if (!targetCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid target character found to switch to."));
		return;
	}

	// 컨트롤러 교체
	AController* playerController = this;
	AController* aiController = targetCharacter->GetController();

	if (playerController) playerController->UnPossess();
	if (aiController) aiController->UnPossess();

	playerController->Possess(targetCharacter);
	aiController->Possess(playerCharacter);

	// 캠프 교체
	playerCharacter->SetCamp_Ally();
	targetCharacter->SetCamp_Player();

	// UI/리더 갱신
	_curCamp->_characterChanged.Broadcast(targetCharacter);
	_curCamp->LeaderChange(targetCharacter);
}

void ACPlayerController::DropItemByClick()
{
	int32 index = -1;
	if (_invenWidget)
		index = _invenWidget->_curIndex;

	auto dropItem = _invenComponent->RemoveItem(index);

	auto player = Cast<ACharacterBase>(GetPawn());
	if (player)
	{
		player->DropItem(dropItem);
	}
}

void ACPlayerController::UseItemByClick()
{
	int32 index = -1;
	if (_invenWidget)
		index = _invenWidget->_curIndex;

	auto useItemData = _invenComponent->GetItemData_Index(index);
	if (useItemData.type == ItemType::NONE)
		return;

	_invenComponent->RemoveItem(index);
	auto useItem = ITEM_M->GetItem(useItemData.id);

	auto player = Cast<APlayerCharacter>(GetPawn());
	if (player && useItem && useItem->GetData().type == ItemType::EQUIPMENT)
	{
		_invenComponent->EquipItem(player, useItem);
	}
	else if (player && useItem)
	{
		useItem->UseItem(player);
	}
}
