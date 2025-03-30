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

	//_loc = CreateDefaultSubobject<USceneComponent>("Loc");
	_sceneComponent = CreateDefaultSubobject<USceneComponent>("Transform");
	_collider = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	_projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("projectileComponent");
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = _sceneComponent;
	_collider->SetupAttachment(RootComponent);
	_mesh->SetupAttachment(_collider);

	


}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::FireDirection(const FVector& direction)
{
	_projectileComponent->Velocity = direction * _projectileComponent->InitialSpeed;
}

void AProjectileBase::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	if (_owner == nullptr)
		return;

	ACharacterBase* targetCharacter = Cast<ACharacterBase>(OtherActor);
	if (targetCharacter->GetChannel() == _owner->GetChannel())
		return;

	auto victim = Cast<ACharacterBase>(OtherActor);
	if (victim)
	{
		FDamageEvent dEvent;
		victim->TakeDamage(_damage, dEvent, _owner->GetController(), _owner);

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
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
