// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AllyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AEnemyCharacter::CheckEnemy(AActor* target)
{
	auto temp = Cast<AAllyCharacter>(target);
	if (temp)
		return true;

	return false;
}
