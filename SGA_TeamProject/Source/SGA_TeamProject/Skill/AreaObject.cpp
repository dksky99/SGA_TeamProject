// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaObject.h"

#include "Components/DecalComponent.h"
#include "../Effect/EffectBase.h"
AAreaObject::AAreaObject()
{
	PrimaryActorTick.bCanEverTick = true;
	_sceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	_decalComponent = CreateDefaultSubobject<UDecalComponent>("Decal");
	RootComponent = _sceneComponent;
	_decalComponent->SetupAttachment(RootComponent);
	_decalComponent->SetRelativeLocation(FVector(0, 0, -88));
	SetScale(300, 300);
}

void AAreaObject::BeginPlay()
{
	Super::BeginPlay();


	_runTime = 0.0f;

	_endEvent.AddUObject(this, &AAreaObject::DeActiveEvent);

	if (_effectClass == nullptr)
		return;
	_effect = GetWorld()->SpawnActor<AEffectBase>(_effectClass);

	_effect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_effect->Stop();
}

void AAreaObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_bIsPlay == false)
		return;

	_runTime += DeltaTime;


	float ratio = _runTime / _delayTime;

	FVector curScale = GetActorScale();
	if (_runTime > _delayTime)
	{
		if (_endEvent.IsBound())
			_endEvent.Broadcast();

		curScale.X = 0.0f;
		curScale.Y = 0.0f;

		SetActorScale3D(curScale);

	}

	curScale.X = ratio * _areaRadius;
	curScale.Y = ratio * _areaRadius;

	SetActorScale3D(curScale);


}

void AAreaObject::Play(FVector pos)
{
	
	SetActorLocation(pos);
	Activate();
	if(_effect)
	_effect->Play(pos);
}

void AAreaObject::DeActiveEvent()
{
	Deactivate();
}

void AAreaObject::SetScale(float x, float y)
{

	_decalComponent->DecalSize = FVector(x, y, 5.0f);
}

void AAreaObject::Activate()
{
	_bIsPlay = true;
	SetActorHiddenInGame(false);
}

void AAreaObject::Deactivate()
{
	_runTime = 0.0f;
	_bIsPlay = false;
	SetActorHiddenInGame(true);

}
