#include "CharacterBase.h"


#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "Components/Button.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/WidgetComponent.h"
#include "../UI/HpBar.h"

#include "../CGameInstance.h"
#include "CharacterAnimInstance.h"

#include "Engine/DamageEvents.h"
#include "Engine/OverlapResult.h"

#include "StatComponent.h"
#include "SkillComponent.h"
#include "DamageLoggingComponent.h"
#include "../Controller/CPlayerController.h"

#include "NPCBase.h"
#include "../Item/ItemManager.h"

#include "../Helper/H_Targetting.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88.0f), FRotator(0, -90, 0));
	GetMesh()->SetCollisionProfileName(FName(TEXT("NoCollision")));
	_statComponent = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
	_dmgLogComponent = CreateDefaultSubobject<UDamageLoggingComponent>(TEXT("DmgLog"));
	_skillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("Skill"));

	_hpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpBarWidget->SetupAttachment(GetMesh());
	_hpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	_hpBarWidget->SetRelativeLocation(FVector(0, 0, 230.0f));

	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Character")));
	_camp = ECamp::None;
	//_channel = ECollisionChannel::ECC_GameTraceChannel2;
	_targetType = ETargettingType::Revenge;
	_defaultTargetType = ETargettingType::MostNear;
	_targetChangeFrequently = false;
	


}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ACharacterBase::UnPossessed()
{
	Super::UnPossessed();

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
	FVector forward = GetControlRotation().Vector();
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
	FRotator controlRot = GetControlRotation();
	FVector right = FRotationMatrix(controlRot).GetUnitAxis(EAxis::Y);
	AddMovementInput(right * value * _statComponent->GetSpeed());
}

void ACharacterBase::Dead()
{
	_animInstance->PlayAnimMontage(_deadAnimMontage);

	_isUnable = true;
	ACPlayerController* playerController = Cast<ACPlayerController>(Controller);
	if (playerController)
	{
		playerController->CharacterChange();
		this->SetActorEnableCollision(false);
		return;
	}

	if (_camp == ECamp::Enemy)
	{
		DropRandomItem();
	}

	auto player = Cast<APlayerCharacter>(this);
	if (player)
		player->NPCInteract();

	if (Controller)
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
	if (_isAttack || _statComponent->IsDead())
		return;

	_isAttack = true;
	//UE_LOG(LogTemp, Log, TEXT(" curAttack %d"), _curAttackSection);
	if (_animInstance)
	{
		_animInstance->PlayAnimMontage(_attackAnimMontage);
		_curAttackSection = (_curAttackSection + 1) % _maxCombo;
		_animInstance->JumpToSection(_curAttackSection);
	}

}

void ACharacterBase::TryAbility1()
{

	if (_isAttack || _statComponent->IsDead())
		return;

	_skillComponent->PlaySkill1();
}

void ACharacterBase::TryAbility1Aiming()
{
	if (_isAttack || _statComponent->IsDead())
		return;

	_skillComponent->DrawSkill1();
}

void ACharacterBase::TryAbility2()
{
	if (_isAttack || _statComponent->IsDead())
		return;

	_skillComponent->PlaySkill2();
}

void ACharacterBase::TryAbility2Aiming()
{
	if (_isAttack || _statComponent->IsDead())
		return;

	_skillComponent->DrawSkill2();
}

void ACharacterBase::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{


	_isAttack = false;
	_skillComponent->SkillUsingFinish();
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
	float attackRadius = _attackRadius;
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
		ACharacterBase* victim = Cast<ACharacterBase>(hitResult.GetActor());
		if (victim)
		{
			FDamageEvent damageEvent = FDamageEvent();

			FVector hitPoint = hitResult.ImpactPoint;
			//EFFECT_M->PlayEffect("MeleeAttack", hitPoint);
			victim->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);

			if (_particleEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation
				(
					GetWorld(),            // 현재 월드
					_particleEffect,       // 에디터에서 세팅한 파티클
					hitPoint,			   // 위치
					FRotator::ZeroRotator, // 회전
					FVector(1.0f),         // 스케일
					true                   // Auto Destroy (자동 제거)
				);
			}
		}
		

		FDamageEvent damageEvent;

		hitResult.GetActor()->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);
		

	}

	//DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);

}

float ACharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 dmg = _statComponent->AddCurHp(-Damage, DamageCauser);
	auto causer = Cast<ACharacterBase>(DamageCauser);
	if (DamageCauser)
		_dmgLogComponent->Logging(causer, dmg);
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

void ACharacterBase::AddSpeed(int32 value)
{
	_statComponent->AddSpeed(value);
}

void ACharacterBase::AddMaxHp(int32 value)
{
	_statComponent->AddMaxHp(value);
}

void ACharacterBase::AddAtk(int32 value)
{
	_statComponent->AddAtk(value);
}

void ACharacterBase::AddHp(int32 value)
{

	_statComponent->AddCurHp(value);
}

void ACharacterBase::AddExp(int32 value)
{

	_statComponent->AddExp(value);
}

void ACharacterBase::DropItem(int32 id)
{
	if (id == -1)
		return;

	FVector playerLocation = GetActorLocation();

	float dropRadius = 200.0f;
	FVector randOffset = FMath::VRand() * FMath::FRandRange(100.0f, dropRadius);
	FVector dropLocation = playerLocation + randOffset;
	dropLocation.Z = playerLocation.Z;

	if (ITEM_M)
	{
		ITEM_M->SpawnItem(id, dropLocation);
	}
}

void ACharacterBase::DropRandomItem()
{
	float randNum = FMath::FRand();

	if (randNum < 0.9f)
		DropItem(101);
	if (randNum < 0.7f)
		DropItem(102);
	if (randNum < 0.5f)
		DropItem(103);
}

bool ACharacterBase::IsAlive()
{
	return !_statComponent->IsDead();
}

int32 ACharacterBase::GetCurHP()
{
	return _statComponent->GetCurHp();
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
	//UE_LOG(LogTemp, Log, TEXT(" SetCamp_None %d"),(int32)(_channel));

	bUseControllerRotationYaw = true;
}

void ACharacterBase::SetCamp_Player()
{
	auto con = Cast<APlayerController>(GetController());
	if (con == nullptr)
		return;

	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Player")));

	_camp = ECamp::Player;
	_channel = ECC_GameTraceChannel7;
	//UE_LOG(LogTemp, Log, TEXT(" SetCamp_Player %d"),(int32)(_channel));
	bUseControllerRotationYaw = false;
	
}

void ACharacterBase::SetCamp_Ally()
{
	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Ally")));
	_camp = ECamp::Ally;
	_channel = ECC_GameTraceChannel7;
	//UE_LOG(LogTemp, Log, TEXT(" SetCamp_Ally %d"),(int32)(_channel));
	bUseControllerRotationYaw = true;
}

void ACharacterBase::SetCamp_Enemy()
{
	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Enemy")));
	_camp = ECamp::Enemy;
	_channel = ECC_GameTraceChannel8;
	//UE_LOG(LogTemp, Log, TEXT(" ECC_GameTraceChannel9 %d"),(int32)(_channel));
	bUseControllerRotationYaw = true;
}

UDamageLoggingComponent* ACharacterBase::GetLogComponent()
{
	return _dmgLogComponent;
}





