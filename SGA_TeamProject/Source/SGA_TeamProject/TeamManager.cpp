// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamManager.h"

#include "Controller/CAIController.h"
#include "Controller/CPlayerController.h"
#include "Engine/EngineTypes.h"

#include "Engine/OverlapResult.h"


#include "Controller/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

// Sets default values for this component's properties
UTeamManager::UTeamManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;


	// ...
}


// Called when the game starts
void UTeamManager::BeginPlay()
{
	Super::BeginPlay();

	// 팀 매니저를 소유한 캐릭터가 어느 캠프인지 캠프 저장
	auto pawn = Cast<AController>(GetOwner())->GetPawn();
	auto character = Cast<ACharacterBase>(pawn);
	if (character)
	{
		_ownerCharacter = character;
		_camp.AddUnique(character);
		_teamChanged.Broadcast(character);
		_characterChanged.Broadcast(character);
		UE_LOG(LogTemp, Error, TEXT("Add Player"));
	}
}


// Called every frame
void UTeamManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FindCharacter();
}

bool UTeamManager::IsSameTeam(ECamp a, ECamp b)
{
	// None은 항상 다른 팀 취급
	if (a == ECamp::None || b == ECamp::None)
		return false;

	// Player와 Ally는 같은 팀
	if ((a == ECamp::Player || a == ECamp::Ally) &&
		(b == ECamp::Player || b == ECamp::Ally))
	{
		return true;
	}

	// Enemy는 Enemy끼리만 같은 팀
	if (a == ECamp::Enemy && b == ECamp::Enemy)
	{
		return true;
	}

	return false;
}

ACharacterBase* UTeamManager::FindCharacter()
{
	float sphereRadius = 500.0f;
	FVector pos = _ownerCharacter->GetActorLocation();

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams params(NAME_None, false, _ownerCharacter);
	bool result = GetWorld()->OverlapMultiByChannel
	(
		overlapResults,
		pos,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(sphereRadius),
		params
	);

	for (auto& overlapResult : overlapResults)
	{
		ACharacterBase* targetCharacter = Cast<ACharacterBase>(overlapResult.GetActor());
		if (targetCharacter && targetCharacter != _ownerCharacter)
		{
			if (IsSameTeam(_ownerCharacter->GetCamp(), targetCharacter->GetCamp()))
			{
				if (!_camp.Contains(targetCharacter))
				{
					_camp.AddUnique(targetCharacter);
					_teamChanged.Broadcast(targetCharacter);
					UE_LOG(LogTemp, Error, TEXT("%s : %d"), *targetCharacter->GetName(), _camp.Num());

					SetLeader(targetCharacter);
					
				}
			}
		}
	}

	return nullptr;
}

void UTeamManager::SetLeader(ACharacterBase* member)
{
	auto temp = Cast<ACAIController>(member->GetController());
	if (temp)
	{
		temp->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Leader")), _ownerCharacter);
	}
}

void UTeamManager::LeaderChange(ACharacterBase* leader)
{
	_ownerCharacter = leader;
	for (auto member : _camp)
	{
		SetLeader(member);
	}
}


