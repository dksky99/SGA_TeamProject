// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "EngineUtils.h"

#include "../Character/CharacterBase.h"
#include "../Character/InvenComponent.h"

#include "../TeamManager.h"

ACPlayerController::ACPlayerController()
{
	_invenComponent = CreateDefaultSubobject<UInvenComponent>(TEXT("InvenComponent"));
	_curCamp = CreateDefaultSubobject<UTeamManager>(TEXT("CampManager"));
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

			// 인덱스 업데이트
			_curPlayerIndex = (_curPlayerIndex + 1) % _curCamp->GetTeamMembers().Num();
		}
	}
}
