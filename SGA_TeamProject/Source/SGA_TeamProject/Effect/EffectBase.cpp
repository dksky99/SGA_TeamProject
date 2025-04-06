// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

#include "NiagaraComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraSystem.h"


// Sets default values
AEffectBase::AEffectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_sceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComponent");

	RootComponent = _sceneComponent;
	_particleComponent->SetupAttachment(_sceneComponent);
	_particleComponent->OnSystemFinished.AddDynamic(this, &AEffectBase::Finished_Particle);
}

// Called when the game starts or when spawned
void AEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectBase::SetParticle(UParticleSystem* particle)
{
	if (particle->IsValidLowLevel())
	{
		_particleComponent->SetTemplate(particle);
		_particleComponent->OnSystemFinished.AddDynamic(this, &AEffectBase::Finished_Particle);
	}
}

void AEffectBase::Stop()
{
	_particleComponent->DeactivateSystem();
}

void AEffectBase::Play(FVector pos)
{
	SetActorLocation(pos);
	UE_LOG(LogTemp, Warning, TEXT("[EffectBase] Playing at: %s"), *pos.ToString());

	if (_particleComponent->Template)
	{
		UE_LOG(LogTemp, Warning, TEXT("[EffectBase] Template Set: %s"), *_particleComponent->Template->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[EffectBase] Template NOT SET!"));
	}
	_particleComponent->Activate(true);
}

bool AEffectBase::IsActive()
{
	return  _particleComponent->IsActive();
}

void AEffectBase::Finished_Particle(UParticleSystemComponent* pSystem)
{
	pSystem->DeactivateSystem();
}

