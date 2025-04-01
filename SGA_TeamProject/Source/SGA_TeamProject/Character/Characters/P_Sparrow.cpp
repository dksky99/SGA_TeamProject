// Fill out your copyright notice in the Description page of Project Settings.


#include "P_Sparrow.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "Engine/DamageEvents.h"
#include "Engine/OverlapResult.h"


#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


#include "../StatComponent.h"
#include "../../Object/ProjectileArrow.h"
void AP_Sparrow::AttackHit()
{

	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = 25.0f;
	FVector fwd = GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = GetActorLocation();
	FVector end = start + fwd * attackRange;
	FVector center = start + (end - start) * 0.5;

	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_channel,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		ACharacterBase* victim = Cast<ACharacterBase>(hitResult.GetActor());
		if (victim)
		{
			FDamageEvent damageEvent = FDamageEvent();

			FVector hitPoint = hitResult.ImpactPoint;
			//EFFECT_M->PlayEffect("MeleeAttack", hitPoint);
			victim->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);

			if (_particleEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation
				(
					GetWorld(),            // 현재 월드
					_particleEffect,       // 에디터에서 세팅한 파티클
					hitPoint,			   // 위치
					FRotator::ZeroRotator, // 회전
					FVector(1.0f),         // 스케일
					true                   // Auto Destroy (자동 제거)
				);
			}
		}


		FDamageEvent damageEvent;

		hitResult.GetActor()->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);

}
