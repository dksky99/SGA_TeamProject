// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "Components/CapsuleComponent.h"
#include "../Controller/CPlayerController.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));

	_mesh->SetupAttachment(_collider);

	RootComponent = _collider;
}

void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_collider->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	auto gameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());
	if (!_dataIsSet && gameInstance)
	{
		const auto data = gameInstance->GetItemData_ID(GetData().id);
		SetData(data);
	}
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::Activate()
{
	SetActive(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	_collider->SetSimulatePhysics(true);
	_collider->SetEnableGravity(true);
}

void AItemBase::Deactivate()
{
	SetActive(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	_collider->SetSimulatePhysics(false);
	_collider->SetEnableGravity(false);
}

void AItemBase::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
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

void AItemBase::SetData(const FItemData& itemData)
{
	_itemData = itemData;

	_dataIsSet = true;
}

