// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


#include "Components/CapsuleComponent.h"
#include "Components/Button.h"


#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"


#include "Engine/DamageEvents.h"
#include "Engine/OverlapResult.h"

#include "Blueprint/UserWidget.h"

#include "../CGameInstance.h"
#include "../Controller/CPlayerController.h"
#include "StatComponent.h"

#include "InvenComponent.h"
#include "../UI/InvenUI.h"

#include "NPCBase.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
