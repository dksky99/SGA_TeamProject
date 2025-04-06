// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileMultiple.h"
#include "Components/capsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Character/CharacterBase.h"
#include "Engine/DamageEvents.h"

void AProjectileMultiple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AProjectileMultiple::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{

	if (_owner == nullptr)
		return;
	if (OtherActor == this)
		return;

	ACharacterBase* targetCharacter = Cast<ACharacterBase>(OtherActor);
	if (targetCharacter == nullptr)
		return;
	if (targetCharacter == _owner)
		return;

	if (targetCharacter->GetChannel() == _owner->GetChannel())
		return;

	auto victim = Cast<ACharacterBase>(OtherActor);
	if (victim)
	{
		FDamageEvent dEvent;
		victim->TakeDamage(_damage, dEvent, _owner->GetController(), _owner);
		
	}
}
