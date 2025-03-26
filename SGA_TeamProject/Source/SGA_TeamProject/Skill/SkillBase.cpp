// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "../Character/CharacterBase.h"

// Sets default values
ASkillBase::ASkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	_curTime += DeltaTime;
	_curTime = FMath::Min(_curTime, _coolTime);


}

void ASkillBase::SkillAiming()
{
}

void ASkillBase::SKillBegin()
{
	_curTime = 0.0f;
}

void ASkillBase::SkillHit()
{
	UE_LOG(LogTemp, Error, TEXT("SkillDefaultHit"));
}



void ASkillBase::SkillEnd()
{
}

void ASkillBase::SetOwner(ACharacterBase* owner)
{
	_owner = owner;
}

