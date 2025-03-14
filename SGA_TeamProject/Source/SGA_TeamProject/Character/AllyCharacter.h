// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "AllyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AAllyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AAllyCharacter();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual bool CheckEnemy(AActor* target) override;
	
};
