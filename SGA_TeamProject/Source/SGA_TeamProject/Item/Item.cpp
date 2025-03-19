// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/Item.h"

#include "Components/CapsuleComponent.h"

#include "../Character/PlayerCharacter.h"
#include "../Controller/CPlayerController.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));

	_mesh->SetupAttachment(_collider);

	RootComponent = _collider;
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_collider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Activate()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AItem::Deactivate()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

bool AItem::IsActive()
{
	return !IsHidden() && GetActorEnableCollision();
}

void AItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	auto character = Cast<APlayerCharacter>(OtherActor);
	if (character)
	{
		auto player = Cast<ACPlayerController>(character->GetController());
		if (player)
		{
			character->AddItem(this);
		}
	}
}

