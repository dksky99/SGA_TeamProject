// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ETargettingType :uint8
{
	MostNear  UMETA(DisplayName = "MostNear"),
	MostLowHP UMETA(DisplayName = "MostLowHP"),
	Revenge UMETA(DisplayName = "Revenge"),
	Max
};
/**
 * 
 */
class SGA_TEAMPROJECT_API H_Targetting
{
public:

	static AActor* MostNearByTarget(TArray<AActor*>& arr, const AActor* existing, const AActor* curPawn);
	static AActor* MostLowHpTarget(TArray<AActor*>& arr, const AActor* existing, const AActor* curPawn);
	static AActor* RevengeTarget(TArray<AActor*>& arr, const AActor* existing, const AActor* curPawn);
};
