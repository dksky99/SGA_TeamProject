// Fill out your copyright notice in the Description page of Project Settings.


#include "P_Sparrow.h"
#include "../../Object/ProjectileArrow.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "../StatComponent.h"
void AP_Sparrow::AttackHit()
{


	float attackRange = _attackRange;

	FVector startPos = GetMesh()->GetSocketLocation(TEXT("Fire_Pos"));
	FVector dir = _camera->GetForwardVector();
	auto projectile = GetWorld()->SpawnActor<AProjectileArrow>(_arrow, startPos, FRotator::ZeroRotator);
	projectile->FireDirection(dir);
	projectile->SetOwner(this);
	projectile->SetDamage(_statComponent->GetAtk());





}
