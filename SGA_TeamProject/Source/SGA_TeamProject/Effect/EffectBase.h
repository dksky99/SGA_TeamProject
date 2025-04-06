// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectBase.generated.h"

UCLASS()
class SGA_TEAMPROJECT_API AEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetParticle(class UParticleSystem* particle);

	void Stop();
	void Play(FVector pos);
	bool IsActive();
	UFUNCTION()
	void Finished_Particle(class UParticleSystemComponent* pSystem);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = "true"))
	class USceneComponent* _sceneComponent;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = "true"))
	class UParticleSystemComponent* _particleComponent;



};
