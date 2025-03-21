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
	float attackRadius = 25.0f;
	FVector fwd = GetActorForwardVector();
	FQuat qRot = FQuat::FindBetweenVectors(FVector::UpVector, fwd);
	FVector start = GetActorLocation();
	FVector end = start + fwd * attackRange;
	FVector center = start + (end - start) * 0.5;

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
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;



		FDamageEvent damageEvent;

		hitResult.GetActor()->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);


	}

	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5, attackRadius, qRot, drawColor, false, 3.0f);

}
