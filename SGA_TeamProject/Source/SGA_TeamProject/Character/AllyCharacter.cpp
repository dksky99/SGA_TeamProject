// Fill out your copyright notice in the Description page of Project Settings.


#include "AllyCharacter.h"
#include "EnemyCharacter.h"

AAllyCharacter::AAllyCharacter()
{
}

void AAllyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAllyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAllyCharacter::CheckEnemy(AActor* target)
{
	auto temp = Cast<AEnemyCharacter>(target);
	if (temp)
		return true;

	return false;
}
