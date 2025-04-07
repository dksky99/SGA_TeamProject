

#include "PlayerCharacter.h"


#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


#include "Components/CapsuleComponent.h"
#include "Components/Button.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "Engine/DamageEvents.h"
#include "Engine/OverlapResult.h"

#include "Blueprint/UserWidget.h"

#include "../CGameInstance.h"
#include "../Controller/CPlayerController.h"
#include "StatComponent.h"
#include "SkillComponent.h"

#include "InvenComponent.h"
#include "../UI/InvenUI.h"
#include "../UI/EquipUI.h"

#include "NPCBase.h"

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

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
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
		enhancedInputComponent->BindAction(_itemDropAction, ETriggerEvent::Triggered, this, &APlayerCharacter::DropItemByKey);
		enhancedInputComponent->BindAction(_invenAction, ETriggerEvent::Triggered, this, &APlayerCharacter::InvenOpen);
		enhancedInputComponent->BindAction(_NPCAction, ETriggerEvent::Triggered, this, &APlayerCharacter::NPCInteract);
		enhancedInputComponent->BindAction(_ability1Action, ETriggerEvent::Started, this, &APlayerCharacter::Abillity1_Press);
		enhancedInputComponent->BindAction(_ability1Action, ETriggerEvent::Completed, this, &APlayerCharacter::Abillity1_Release);
		enhancedInputComponent->BindAction(_ability2Action, ETriggerEvent::Started, this, &APlayerCharacter::Abillity2_Press);
		enhancedInputComponent->BindAction(_ability2Action, ETriggerEvent::Completed, this, &APlayerCharacter::Abillity2_Release);
		ACPlayerController* controller = Cast<ACPlayerController>(Controller);
		if (controller)
			enhancedInputComponent->BindAction(_characterChange, ETriggerEvent::Started, controller, &ACPlayerController::CharacterChange);
	}
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	if (_statComponent->IsDead() || _isNPCInteract)
		return;

	FVector2D moveVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{

			UpDown(moveVector.Y);
			RightLeft(moveVector.X);

			GetCharacterMovement()->bUseControllerDesiredRotation = true;
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

		float degree = FMath::FindDeltaAngleDegrees(GetActorRotation().Yaw, GetControlRotation().Yaw);

		// 카메라 오른쪽을 넘어감, 나는 정면
		if (degree > 90.0f)
		{
			_isTurnRight = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		// 카메라 왼쪽을 넘어감, 나는 정면
		else if (degree < -90.0f)
		{
			_isTurnLeft = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		// 움직이거나, 공격
		else if (GetCharacterMovement()->Velocity.Size() > 0.1f || _isAttack)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		// 카메라, 정면 각도 차이의 절대값이 0.1 미만
		else if (FMath::Abs(degree) < 0.1f)
		{
			_isTurnLeft = false;
			_isTurnRight = false;
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
		}
	}
}

void APlayerCharacter::TryJump(const FInputActionValue& value)
{
	if (_isUnable || _isNPCInteract)
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

	if (_isUnable || _isNPCInteract)
		return;
	bool isPress = value.Get<bool>();
	if (isPress)
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;

		TryAttack();
	}
}

void APlayerCharacter::Abillity1_Press(const FInputActionValue& value)
{
	if (_isUnable || _isNPCInteract)
		return;

	TryAbility1Aiming();
}

void APlayerCharacter::Abillity1_Release(const FInputActionValue& value)
{
	if (_isUnable || _isNPCInteract)
		return;

	TryAbility1();
}

void APlayerCharacter::Abillity2_Press(const FInputActionValue& value)
{
	if (_isUnable || _isNPCInteract)
		return;

	TryAbility2Aiming();
}


void APlayerCharacter::Abillity2_Release(const FInputActionValue& value)
{
	if (_isUnable || _isNPCInteract)
		return;

	TryAbility2();
}

void APlayerCharacter::DropItemByKey(const FInputActionValue& value)
{
	if (_isUnable || _isNPCInteract)
		return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		auto dropItem = INVEN_COMP->RemoveItem();
		DropItem(dropItem.id);
	}

	UE_LOG(LogTemp, Log, TEXT("Drop Empty Space"));
}

void APlayerCharacter::InvenOpen(const FInputActionValue& value)
{
	if (_isUnable || _isNPCInteract)
		return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		auto controller = Cast<ACPlayerController>(GetController());

		if (_isInvenOpen)
		{
			if (controller)
				controller->HideUI();
			INVEN_UI->RemoveFromViewport();
			EQUIP_UI->RemoveFromViewport();
		}
		else
		{
			if (controller)
				controller->ShowUI();
			INVEN_UI->AddToViewport();
			EQUIP_UI->AddToViewport();
		}

		_isInvenOpen = !_isInvenOpen;
	}

	UE_LOG(LogTemp, Log, TEXT("Inven Open"));
}

void APlayerCharacter::NPCInteract(const FInputActionValue& value)
{
	if (_isAttack)
		return;

	if (_isUnable)
		return;

	bool isPress = value.Get<bool>();
	if (isPress)
	{
		float sphereRadius = 500.0f;
		FVector pos = GetActorLocation();

		TArray<FOverlapResult> overlapResults;
		FCollisionQueryParams params(NAME_None, false, this);
		bool result = GetWorld()->OverlapMultiByChannel(
			overlapResults,
			pos,
			FQuat::Identity,
			ECC_Pawn,
			FCollisionShape::MakeSphere(sphereRadius),
			params
		);

		if (result == false)
		{
			//DrawDebugSphere(GetWorld(), pos, sphereRadius, 12, FColor::Red, false, 0.3f);
			return;
		}

		for (auto& overlapResult : overlapResults)
		{
			auto NPC = Cast<ANPCBase>(overlapResult.GetActor());
			if (NPC && NPC->IsValidLowLevel())
			{
				NPC->Interact();
				//DrawDebugSphere(GetWorld(), pos, sphereRadius, 12, FColor::Green, false, 0.3f);
				UE_LOG(LogTemp, Log, TEXT("NPC"));

				_isNPCInteract = !_isNPCInteract;
				return;
			}
		}

		//DrawDebugSphere(GetWorld(), pos, sphereRadius, 12, FColor::Red, false, 0.3f);
		return;
	}
}

void APlayerCharacter::AddItem(AItemBase* item)
{
	if (item && INVEN_COMP)
	{
		if (INVEN_COMP->IsFull())
			return;

		INVEN_COMP->AddItem(item->GetData());

		item->Deactivate();
	}
}
