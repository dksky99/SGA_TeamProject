// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "../Character/CharacterBase.h"

#include "Components/DecalComponent.h"
#include "Components/SplineComponent.h"
#include "../Helper/H_Relation.h"

// Sets default values
ASkillBase::ASkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sceneComponent = CreateDefaultSubobject<USceneComponent>("Transform");
	_decalComponent = CreateDefaultSubobject<UDecalComponent>("Decal");
	_splineComponent = CreateDefaultSubobject<USplineComponent>("Spline");

	SetRootComponent(_sceneComponent);
	_decalComponent->SetupAttachment(RootComponent);
	_splineComponent->SetupAttachment(RootComponent);

	_decalComponent->SetVisibility(false);
	_splineComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void ASkillBase::BeginPlay()
{
	Super::BeginPlay();
	SkillEnd();
	DrawingFinish();
}

void ASkillBase::StartAiming()
{
	UE_LOG(LogTemp, Error, TEXT("AimingStart"));
	_state = ESkillState::Aiming;
	DrawingStart();
}

void ASkillBase::AITargeting(ACharacterBase* target)
{
	
	StartPreCaution();

}

void ASkillBase::StartPreCaution()
{
	UE_LOG(LogTemp, Error, TEXT("PrecautionStart"));
	_state = ESkillState::Precaution;
	DrawingStart();
}

void ASkillBase::DrawingStart()
{
	_decalComponent->SetActive(true);
	_splineComponent->SetActive(true);
	_decalComponent->SetVisibility(true);
	_splineComponent->SetVisibility(true);
}

void ASkillBase::DrawingFinish()
{
	_decalComponent->SetActive(false);
	_splineComponent->SetActive(false);
	_decalComponent->SetVisibility(false);
	_splineComponent->SetVisibility(false);
}

// Called every frame
void ASkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CoolTimeFlow(DeltaTime);

	switch (_state)
	{
	case ESkillState::Deactivate:
		break;
	case ESkillState::Aiming:
		DrawSkillAiming();
		break;
	case ESkillState::Precaution:
		DrawSkillPrecaution();
		break;
	case ESkillState::Playing:
		SkillTick();
		break;
	default:
		break;
	}
	

}

void ASkillBase::DrawSkillAiming()
{
	UE_LOG(LogTemp, Error, TEXT("Aiming"));
}

void ASkillBase::DrawSkillPrecaution()
{
	UE_LOG(LogTemp, Error, TEXT("Precaution"));
}

void ASkillBase::SKillBegin()
{
	_curTime = 0.0f;
	_state = ESkillState::Precaution;

}

void ASkillBase::SkillHit()
{
	UE_LOG(LogTemp, Error, TEXT("SkillDefaultHit"));
	_state=ESkillState::Playing;
	DrawingFinish();

}

void ASkillBase::SkillTick()
{
	UE_LOG(LogTemp, Error, TEXT("SkillTick"));
}



void ASkillBase::SkillEnd()
{
	_target = nullptr;
	_state = ESkillState::Deactivate;

}

void ASkillBase::Set_Owner(ACharacterBase* owner)
{
	_owner = owner;
	SetActorLocationAndRotation(owner->GetActorLocation(), owner->GetActorRotation());
}

void ASkillBase::SetLocOfFloor()
{
	FVector loc = _loc;
	loc=H_Relation::FindFloorFromLoc(this, 1000, true, loc);
	if (loc != FVector::ZeroVector)
		_loc == loc;

	UE_LOG(LogTemp, Error, TEXT("Drawing: %f %f %f"),_loc.X,_loc.Y,_loc.Z);
}

void ASkillBase::CoolTimeFlow(float DeltaTime)
{
	_curTime += DeltaTime;
	_curTime = FMath::Min(_curTime, _coolTime);
}

