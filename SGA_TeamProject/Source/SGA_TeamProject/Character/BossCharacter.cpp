// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"

#include "DamageLoggingComponent.h"
#include "../UI/DamageLoggingUI.h"

#include "StatComponent.h"
#include "Engine/DamageEvents.h"

void ABossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_damageLogClass)
	{
		_damageLogWidget = CreateWidget<UDamageLoggingUI>(GetWorld(), _damageLogClass);
	}
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	_dmgLogComponent->_dmgLogChanged.AddUObject(this, &ABossCharacter::DamageLogUpdate);

	if (_damageLogWidget)
	{
		_damageLogWidget->AddToViewport();
	}
}

void ABossCharacter::DamageLogUpdate()
{
	if (_damageLogWidget && _dmgLogComponent)
	{
		auto damageList = _dmgLogComponent->GetValidList();
		auto damageLogWidget = Cast<UDamageLoggingUI>(_damageLogWidget);
		if (damageLogWidget)
		{
			damageLogWidget->UpdateList(damageList);
		}
	}

}

void ABossCharacter::AttackHit()
{
	
	TArray <FHitResult> hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _attackRange;
	float attackRadius = _attackRange;
	FVector fwd = GetActorForwardVector();
	FVector start = GetActorLocation() + fwd * attackRange+FVector::UpVector*attackRange;
	FVector end = start - FVector::UpVector * attackRange * 2;
	FVector center = start + (end - start) * 0.5;
	FQuat qRot = FQuat::FindBetweenVectors(start, end);

	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT hitResult,
		start,
		end,
		FQuat::Identity,
		_channel,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;
	if (bResult)
	{
		drawColor = FColor::Red;
		for (auto hit : hitResult)
		{
			if (hit.GetActor()->IsValidLowLevel())
			{



				FDamageEvent damageEvent;

				hit.GetActor()->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);


			}

		}

	}

	UE_LOG(LogTemp, Error, TEXT("BossAttack %f %f %f"),center.X,center.Y,center.Z);
	

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);

}
