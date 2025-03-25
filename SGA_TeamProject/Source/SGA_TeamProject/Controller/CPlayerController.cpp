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
		_invenWidget->Drop->OnClicked.AddDynamic(this, &ACPlayerController::DropItemByClick);
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
	ACharacterBase* targetCharacter = _curCamp->GetTeamMembers()[_curPlayerIndex];
	if (targetCharacter)
	{
		if (targetCharacter->IsAlive())
		{
			// 두 컨트롤러 가져오기
			AController* playerController = this; // 현재 PlayerController
			AController* aiController = targetCharacter->GetController(); // 타겟의 AI 컨트롤러

			// 각각 UnPossess
			if (playerController) playerController->UnPossess();
			if (aiController) aiController->UnPossess();

			// 컨트롤러 교체 
			playerController->Possess(targetCharacter);
			aiController->Possess(playerCharacter);

			// cmap 교체
			playerCharacter->SetCamp_Ally();
			targetCharacter->SetCamp_Player();

			// UI 업데이트
			_curCamp->_characterChanged.Broadcast(targetCharacter);

			//리더 변경
			_curCamp->LeaderChange(targetCharacter);
		}
			// 인덱스 업데이트
			_curPlayerIndex = (_curPlayerIndex + 1) % _curCamp->GetTeamMembers().Num();
	}
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
