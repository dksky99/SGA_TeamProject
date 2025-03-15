// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "../Character/InvenComponent.h"

ACPlayerController::ACPlayerController()
{
	_invenComponent = CreateDefaultSubobject<UInvenComponent>(TEXT("InvenComponent"));
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
}

void ACPlayerController::ShowUI()
{

	bShowMouseCursor = true;
}

void ACPlayerController::HideUI()
{

	bShowMouseCursor = false;
}
