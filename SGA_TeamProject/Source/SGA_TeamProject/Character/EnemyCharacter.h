// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual bool CheckEnemy(AActor* target) override;
};
