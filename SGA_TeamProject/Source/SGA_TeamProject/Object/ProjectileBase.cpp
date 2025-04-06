// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/capsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Character/CharacterBase.h"
#include "Engine/DamageEvents.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_sceneComponent= CreateDefaultSubobject<USceneComponent>("Scene");
	//_loc = CreateDefaultSubobject<USceneComponent>("Loc");
	_collider = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	_projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("projectileComponent");
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = _sceneComponent;
	_collider->SetupAttachment(RootComponent);
	_mesh->SetupAttachment(_collider);

	Deactivate();

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	Deactivate();
	_collider->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnProjectileOverlap);

}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MeshRotating(DeltaTime);
	if (_bisFire == false)
		return;
	if (CheckDistance())
	{
		Deactivate();
	}

}

void AProjectileBase::ProjectileFire(FVector Start, FVector direction)
{
	SetStartPos(Start);
	FireDirection(direction);
	Activate();
}

void AProjectileBase::FireDirection(const FVector& direction)
{
	
	SetActorRotation(direction.ToOrientationQuat());
	SetStartPos(GetActorLocation());
	_projectileComponent->Velocity = GetActorForwardVector() * _projectileComponent->InitialSpeed;
}

void AProjectileBase::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	if (_owner == nullptr)
		return;
	if (OtherActor == this)
		return;

	ACharacterBase* targetCharacter = Cast<ACharacterBase>(OtherActor);
	if (targetCharacter == nullptr)
		return;
	if (targetCharacter == _owner)
		return;

	if (targetCharacter->GetChannel() == _owner->GetChannel())
		return;

	auto victim = Cast<ACharacterBase>(OtherActor);
	if (victim)
	{
		FDamageEvent dEvent;
		victim->TakeDamage(_damage, dEvent, _owner->GetController(), _owner);
		Deactivate();
	}
}

void AProjectileBase::SetOwner(ACharacterBase* owner)
{
	if (owner == nullptr)
	{
		_owner = nullptr;
		return;
	}

	_owner = owner;
}

void AProjectileBase::Activate()
{

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	_bisFire = true;
}

void AProjectileBase::Deactivate()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	_bisFire = false;
}

void AProjectileBase::SetStartPos(FVector start)
{

	_startPos = start;
	SetActorLocation(_startPos);
}

bool AProjectileBase::CheckDistance()
{
	if (_maxDistance == 0.0f)
		return false;

	float dist = (GetActorLocation() - _startPos).Length();
	if (dist < _maxDistance)
		return false;

	return true;
}

void AProjectileBase::MeshRotating(float deltaTime)
{
	FRotator temp = _collider->GetRelativeRotation();
	temp += _rotating * deltaTime * _rotateSpeed;
	_collider->SetRelativeRotation(temp);

}

