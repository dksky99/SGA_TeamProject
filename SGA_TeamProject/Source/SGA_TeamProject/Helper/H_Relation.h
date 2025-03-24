// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SGA_TEAMPROJECT_API H_Relation
{
public:
	static bool IsInSight(class AActor* user, class AActor* target, float maxAngle);
	static bool IsInDistance(class AActor* user, class AActor* target, float maxDistance);

};
