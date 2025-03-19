// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class SGA_TEAMPROJECT_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned

public:
	// Called every frame


private:
	
};
