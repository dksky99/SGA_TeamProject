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


	virtual void AttackHit() override;
	
protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectileArrow> _arrow;
};
