// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Relation.h"

bool H_Relation::IsInSight(AActor* user, AActor* target, float maxAngle)
{
    if (!user || !target) return false;

    FVector ForwardVector = user->GetActorForwardVector(); // AI의 정면 벡터
    FVector ToTarget = (target->GetActorLocation() - user->GetActorLocation()).GetSafeNormal(); // AI → Target 방향 벡터

    float DotProduct = FVector::DotProduct(ForwardVector, ToTarget); // 두 벡터의 내적 계산
    float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct)); // 내적을 이용해 각도 계산

    return Angle <= maxAngle; // 설정한 각도 이내인지 체크
}

bool H_Relation::IsInDistance(AActor* user, AActor* target, float maxDistance)
{
    if (!user || !target) return false;

    return user->GetDistanceTo(target) <= maxDistance; // 설정한 각도 이내인지 체크
}
