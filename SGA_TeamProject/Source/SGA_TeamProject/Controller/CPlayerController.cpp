// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "../Character/CharacterBase.h"
#include "../Character/InvenComponent.h"

#include "../UI/PartyListUI.h"

ACPlayerController::ACPlayerController()
{
	_invenComponent = CreateDefaultSubobject<UInvenComponent>(TEXT("InvenComponent"));
}

void ACPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_partyListClass)
	{
		_partyListWidget = CreateWidget<UPartyListUI>(GetWorld(), _partyListClass);
	}
}

void ACPlayerController::BeginPlay()
{
	//�θ��� BeginPlay ȣ��. ��ӱ����� �̺�Ʈ�� �θ��� �̺�Ʈ�� ȣ���������
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
	UE_LOG(LogTemp, Warning, TEXT("CharacterChange"));

	ACharacterBase* character = FindNewCharacterForPlayer();
	character->GetController()->UnPossess();

	Possess(character);
}

ACharacterBase* ACPlayerController::FindNewCharacterForPlayer()
{
	for (TActorIterator<ACharacterBase> iter(GetWorld()); iter; ++iter)
	{
		ACharacterBase* character = *iter;

		if (character != GetPawn() && character->IsAlive())
		{
			return character;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("There are no living characters!"));
	return nullptr;
}
