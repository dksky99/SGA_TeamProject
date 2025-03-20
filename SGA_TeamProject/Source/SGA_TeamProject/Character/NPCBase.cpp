// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"

#include "Components/Button.h"
#include "Blueprint/UserWidget.h"

#include "../CharacterAnimInstance.h"
#include "../Controller/CPlayerController.h"
#include "../UI/ShopUI.h"
#include "InvenComponent.h"

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	
	_shopComponent = CreateDefaultSubobject<UInvenComponent>(TEXT("InvenComponent"));
}

void ANPCBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_shopWidgetClass)
	{
		_shopWidget = CreateWidget<UUserWidget>(GetWorld(), _shopWidgetClass);
		UE_LOG(LogTemp, Log, TEXT("Inven Widget Created"));
	}

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		ACPlayerController* MyController = Cast<ACPlayerController>(PlayerController);
		if (MyController && MyController->GetInvenComponent())
		{
			_invenComponent = MyController->GetInvenComponent();
		}
	}
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
	_animInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (_animInstance == nullptr)
		UE_LOG(LogTemp, Error, TEXT("AnimInstace did not Set"));

	auto shopUI = Cast<UShopUI>(_shopWidget);
	if (shopUI)
	{
		shopUI->_getInvenItemInfo.BindUObject(_invenComponent, &UInvenComponent::GetItemData_Index);
		shopUI->_getShopItemInfo.BindUObject(_shopComponent, &UInvenComponent::GetItemData_Index);
		shopUI->Sell->OnClicked.AddDynamic(this, &ANPCBase::ItemSell);
		shopUI->Buy->OnClicked.AddDynamic(this, &ANPCBase::ItemBuy);
	}
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCBase::Interact()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		ACPlayerController* MyController = Cast<ACPlayerController>(PlayerController);
		if (MyController && MyController->GetInvenComponent())
		{
			_invenComponent = MyController->GetInvenComponent();

			OpenUI(MyController);
		}
	}

	return;
}

void ANPCBase::OpenUI(ACPlayerController* controller)
{
	if (_isShopOpen)
	{
		if (controller)
		{
			controller->HideUI();
		}
		_shopWidget->RemoveFromViewport();
	}
	else
	{
		if (controller)
		{
			controller->ShowUI();
		}

		auto shopWidget = Cast<UShopUI>(_shopWidget);
		if (shopWidget)
			shopWidget->UpdateShop(_invenComponent, _shopComponent);

		_shopWidget->AddToViewport();
	}

	_isShopOpen = !_isShopOpen;
}

void ANPCBase::ItemBuy()
{
	if (!_invenComponent || !_shopComponent)
		return;

	auto shopUI = Cast<UShopUI>(_shopWidget);
	if (shopUI)
	{
		auto index = shopUI->_curShopIndex;
		AItem* item = _shopComponent->GetItem_Index(index);

		if (item == nullptr)
			return;

		_shopComponent->RemoveItem(index);
		_invenComponent->AddItem(item);

		shopUI->UpdateShop(_invenComponent, _shopComponent);
	}
}

void ANPCBase::ItemSell()
{
	if (!_invenComponent || !_shopComponent)
		return;

	auto shopUI = Cast<UShopUI>(_shopWidget);
	if (shopUI)
	{
		auto index = shopUI->_curInvenIndex;
		AItem* item = _invenComponent->GetItem_Index(index);

		if (item == nullptr)
			return;

		_invenComponent->RemoveItem(index);
		_shopComponent->AddItem(item);

		shopUI->UpdateShop(_invenComponent, _shopComponent);
	}
}