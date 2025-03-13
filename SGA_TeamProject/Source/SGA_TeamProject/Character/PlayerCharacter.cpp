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

#include "Blueprint/UserWidget.h"

#include "../CGameInstance.h"
#include "../Controller/CPlayerController.h"
#include "StatComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));
	_springArm->bUsePawnControlRotation = true;

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

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent)
	{
		enhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		enhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TryJump);
		enhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
		enhancedInputComponent->BindAction(_itemDropAction, ETriggerEvent::Triggered, this, &APlayerCharacter::DropItem);
		enhancedInputComponent->BindAction(_invenAction, ETriggerEvent::Triggered, this, &APlayerCharacter::InvenOpen);
	}
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	if ( _statComponent->IsDead())
		return;

	FVector2D moveVector = value.Get<FVector2D>();
		UE_LOG(LogTemp, Log, TEXT(" TryMove"));

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{

			UpDown(moveVector.Y);
			RightLeft(moveVector.X);

		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(-lookAxisVector.Y);
	}
}

void APlayerCharacter::TryJump(const FInputActionValue& value)
{
	if (_isUnable)
		return;
	if (value.Get<bool>())
	{
		UE_LOG(LogTemp, Log, TEXT(" Jump Test"));
		Jump();
	}
}

void APlayerCharacter::Attack(const FInputActionValue& value)
{

	if (_isAttack)
		return;

	if (_isUnable)
		return;
	bool isPress = value.Get<bool>();
	if (isPress)
	{


		_isAttack = true;
		UE_LOG(LogTemp, Log, TEXT(" curAttack %d"), _curAttackSection);
		//if (_animInstance)
		//{
		//
		//	_animInstance->PlayAnimMontage();
		//	_curAttackSection = (_curAttackSection + 1) % 5;
		//	_animInstance->JumpToSection(_curAttackSection);
		//}

	}
}


void APlayerCharacter::DropItem(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Log, TEXT("Drop Empty Space"));
}

void APlayerCharacter::InvenOpen(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Log, TEXT("Inven Empty Space"));
}

void APlayerCharacter::Drop()
{
	UE_LOG(LogTemp, Log, TEXT("Empty Space"));
}
