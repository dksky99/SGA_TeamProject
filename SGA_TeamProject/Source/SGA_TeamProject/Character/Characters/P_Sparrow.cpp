// Fill out your copyright notice in the Description page of Project Settings.


#include "P_Sparrow.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "../StatComponent.h"
#include "../../Object/ProjectileArrow.h"
void AP_Sparrow::AttackHit()
{

	FVector startPos = GetMesh()->GetSocketLocation(TEXT("FirePos"));
	FVector dir = _camera->GetForwardVector();
	auto projectile = GetWorld()->SpawnActor<AProjectileArrow>(_projectileClass, startPos, FRotator::ZeroRotator);
	projectile->FireDirection(dir);
	projectile->SetDamage(_statComponent->GetAtk());
	projectile->SetOwner(this);
}
