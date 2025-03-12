#include "CharacterBase.h"


#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "Engine/DamageEvents.h"

#include "StatComponent.h"
#include "../Controller/CPlayerController.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88.0f), FRotator(0, -90, 0));

	_statComponent = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();


	auto animInstance = GetMesh()->GetAnimInstance();
	//Todo:  Get AnimInstance & Delegate Bind


	_statComponent->_deadEvent.AddUObject(this, &ACharacterBase::Dead);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::UpDown(float value)
{

	if (abs(value) < 0.01f)
	{
		return;
	}
	_vertical = value;
	FVector forward = GetActorForwardVector();
	AddMovementInput(forward * value * _statComponent->GetSpeed());
}

void ACharacterBase::RightLeft(float value)
{
	if (abs(value) < 0.01f)
	{
		return;
	}
	_horizontal = value;
	FVector right = GetActorRightVector();
	AddMovementInput(right * value * _statComponent->GetSpeed());
}

void ACharacterBase::Dead()
{

	_isUnable = true;
	Controller->UnPossess();
	this->SetActorEnableCollision(false);
}

void ACharacterBase::DeadActionEnd()
{

	this->SetActorHiddenInGame(true);
	this->SetActorTickEnabled(false);
}



void ACharacterBase::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{


	_isAttack = false;
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
		ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		ACharacterBase* victim = Cast<ACharacterBase>(hitResult.GetActor());
		if (victim)
		{

			FDamageEvent damageEvent;

			victim->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);
		}

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

