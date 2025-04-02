// Fill out your copyright notice in the Description page of Project Settings.


#include "P_Sparrow.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "../StatComponent.h"
#include "../../Object/ProjectileArrow.h"


#include "Engine/DamageEvents.h"
#include "Engine/OverlapResult.h"



#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
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
					GetWorld(),            
					_particleEffect,       
					hitPoint,			   
					FRotator::ZeroRotator, 
					FVector(1.0f),         
					true                   
				);
			}
		}


		FDamageEvent damageEvent;

		hitResult.GetActor()->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);


	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);

}
