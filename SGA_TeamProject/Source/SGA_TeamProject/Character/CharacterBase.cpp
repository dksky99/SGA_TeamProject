#include "CharacterBase.h"


#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "Components/WidgetComponent.h"
#include "../UI/HpBar.h"

#include "../CharacterAnimInstance.h"

#include "Engine/DamageEvents.h"

#include "StatComponent.h"
#include "../Controller/CPlayerController.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88.0f), FRotator(0, -90, 0));
	GetMesh()->SetCollisionProfileName(FName(TEXT("NoCollision")));
	_statComponent = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));

	_hpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpBarWidget->SetupAttachment(GetMesh());
	_hpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	_hpBarWidget->SetRelativeLocation(FVector(0, 0, 230.0f));

	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Character")));
	_camp = ECamp::None;
	//_channel = ECollisionChannel::ECC_GameTraceChannel2;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();


	_animInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (_animInstance == nullptr)
		UE_LOG(LogTemp, Error, TEXT("AnimInstace did not Set"));

	_animInstance->OnMontageEnded.AddDynamic(this, &ACharacterBase::AttackEnd);
	_animInstance->_attackHitDelegate.AddUObject(this, &ACharacterBase::AttackHit);
	_animInstance->_animDeadEvent.AddUObject(this, &ACharacterBase::DeadActionEnd);

	_statComponent->_deadEvent.AddUObject(this, &ACharacterBase::Dead);

	auto hpBar = Cast<UHpBar>(_hpBarWidget->GetWidget());
	if (hpBar)
		_statComponent->_hpChanged.AddUObject(hpBar, &UHpBar::SetHpBarValue);

	SetCamp(_camp);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 일정 거리 이상 멀어지면 hpBar 안 보임
	auto playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		auto playerCameraManager = playerController->PlayerCameraManager;
		if (playerCameraManager)
		{
			FVector cameraLocation = playerCameraManager->GetCameraLocation();
			float distance = FVector::Distance(GetActorLocation(), cameraLocation);

			if (distance > 1000.0f)
				_hpBarWidget->SetVisibility(false);
			else
				_hpBarWidget->SetVisibility(true);
		}
	}


}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::UpDown(float value)
{
	if (_isAttack)
		return;


	if (abs(value) < 0.01f)
	{
		_vertical = 0.0f;
		return;
	}
	_vertical = value;
	FVector forward = GetActorForwardVector();
	AddMovementInput(forward * value * _statComponent->GetSpeed());
}

void ACharacterBase::RightLeft(float value)
{
	if (_isAttack)
		return;

	if (abs(value) < 0.01f)
	{
		_horizontal = 0.0f;
		return;
	}
	_horizontal = value;
	FVector right = GetActorRightVector();
	AddMovementInput(right * value * _statComponent->GetSpeed());
}

void ACharacterBase::Dead()
{
	_animInstance->PlayAnimMontage(_deadAnimMontage);

	_isUnable = true;
	Controller->UnPossess();
	this->SetActorEnableCollision(false);
}



void ACharacterBase::DeadActionEnd()
{
	this->SetActorHiddenInGame(true);
	this->SetActorTickEnabled(false);
}

void ACharacterBase::TryAttack()
{
	if (_isAttack)
		return;
	
	_isAttack = true;
	UE_LOG(LogTemp, Log, TEXT(" curAttack %d"), _curAttackSection);
	if (_animInstance)
	{
		_animInstance->PlayAnimMontage(_attackAnimMontage);
		_curAttackSection = (_curAttackSection + 1) % _maxCombo;
		_animInstance->JumpToSection(_curAttackSection);
	}

}

void ACharacterBase::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{


	_isAttack = false;
}

bool ACharacterBase::CheckEnemy(AActor* target)
{
	auto temp = Cast<ACharacterBase>(target);
	if (temp)
		return true;

	return false;
}

void ACharacterBase::AttackHit()
{

	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = 25.0f;
	FVector fwd = GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = GetActorLocation();
	FVector end = start + fwd * attackRange;
	FVector center = start + (end - start) * 0.5;

	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_channel,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		

		FDamageEvent damageEvent;

		hitResult.GetActor()->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);
		

	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);

}

float ACharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 dmg = _statComponent->AddCurHp(-Damage, DamageCauser);
	if (_statComponent->IsDead())
	{
		_statComponent->_deadEvent.Broadcast();
		//공격자가 플레이어라면
		auto attackerController = Cast<ACPlayerController>(EventInstigator);
		if (attackerController)
		{

			if (DamageCauser != nullptr)
			{
				ACharacterBase* temp = Cast<ACharacterBase>(DamageCauser);
				if (temp != nullptr)
				{
					temp->AddExp(100);
				}
			}

		}

	}



	return dmg;
}

void ACharacterBase::AddHp(int32 value)
{

	_statComponent->AddCurHp(value);
}

void ACharacterBase::AddExp(int32 value)
{

	_statComponent->AddExp(value);
}

void ACharacterBase::SetCamp(ECamp camp)
{
	switch (camp)
	{
	case ECamp::None:
		SetCamp_None();
		break;
	case ECamp::Player:
		SetCamp_Player();
		break;
	case ECamp::Ally:
		SetCamp_Ally();
		break;
	case ECamp::Enemy:
		SetCamp_Enemy();
		break;
	case ECamp::Max:
		break;
	default:
		break;
	}
}

void ACharacterBase::SetCamp_None()
{


	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Character")));
	_camp = ECamp::None;
	_channel = ECC_GameTraceChannel2;
	UE_LOG(LogTemp, Log, TEXT(" SetCamp_None %d"),(int32)(_channel));
}

void ACharacterBase::SetCamp_Player()
{
	auto con = Cast<APlayerController>(GetController());
	if (con == nullptr)
		return;

	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Player")));

	_camp = ECamp::Player;
	_channel = ECC_GameTraceChannel8;
	UE_LOG(LogTemp, Log, TEXT(" SetCamp_Player %d"),(int32)(_channel));
	
}

void ACharacterBase::SetCamp_Ally()
{
	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Ally")));
	_camp = ECamp::Ally;
	_channel = ECC_GameTraceChannel8;
	UE_LOG(LogTemp, Log, TEXT(" SetCamp_Ally %d"),(int32)(_channel));
}

void ACharacterBase::SetCamp_Enemy()
{
	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Enemy")));
	_camp = ECamp::Enemy;
	_channel = ECC_GameTraceChannel9;
	UE_LOG(LogTemp, Log, TEXT(" ECC_GameTraceChannel9 %d"),(int32)(_channel));
}

