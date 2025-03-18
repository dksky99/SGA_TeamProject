// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Targetting.h"
#include "../Character/CharacterBase.h"

AActor* H_Targetting::MostNearByTarget(TArray<AActor*>& arr, const AActor* existing, const AActor* curPawn)
{
	Algo::Sort(arr, [curPawn](const AActor* A1, const AActor* A2) {
		return curPawn->GetDistanceTo(A1) < curPawn->GetDistanceTo(A2);
		});


	return arr[0];
}

AActor* H_Targetting::MostLowHpTarget(TArray<AActor*>& arr, const AActor* existing, const AActor* curPawn)
{
	Algo::Sort(arr, [](AActor* a1, AActor* a2)->bool {
		auto c1 = Cast<ACharacterBase>(a1);
		auto c2 = Cast<ACharacterBase>(a2);

		return c1->GetCurHP() < c2->GetCurHP();

		});

	return arr[0];
}

AActor* H_Targetting::RevengeTarget(TArray<AActor*>& arr, const AActor* existing, const AActor* curPawn)
{
	return nullptr;
}
