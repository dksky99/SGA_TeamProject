// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PlayerCharacter.h"
#include "P_Sparrow.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API AP_Sparrow : public APlayerCharacter
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void AttackHit() override;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectileBase> _projectileClass;
	
	UPROPERTY()
	TArray<class AProjectileBase*> _projectiles;
	
	int32 _curFire = 0;
};
