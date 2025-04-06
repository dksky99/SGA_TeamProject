// Fill out your copyright notice in the Description page of Project Settings.


#include "P_Sparrow.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

#include "../StatComponent.h"
#include "../../Object/ProjectileArrow.h"
#include "../../Object/ProjectileBase.h"


#include "Engine/DamageEvents.h"
#include "Engine/OverlapResult.h"



#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
void AP_Sparrow::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 5; i++)
	{
		auto projectile = GetWorld()->SpawnActor<AProjectileBase>(_projectileClass);

		projectile->SetOwner(this);
		int32 dmg = GetStatComponent()->GetAtk();
		projectile->SetDamage(dmg);
		_projectiles.Add(projectile);
	}
}
void AP_Sparrow::AttackHit()
{

	_curFire = _curFire % _projectiles.Num();

	_projectiles[_curFire]->SetOwner(this);
	int32 dmg = GetStatComponent()->GetAtk();
	_projectiles[_curFire]->SetDamage(dmg);

	_projectiles[_curFire++]->ProjectileFire(GetMesh()->GetSocketLocation(TEXT("FirePos")), GetActorForwardVector());

}
