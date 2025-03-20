// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySlotUI.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "../Character/CharacterBase.h"
#include "../Character/StatComponent.h"

void UPartySlotUI::Setup(ACharacterBase* character)
{
	if (!character)
		return;

	Name->SetText(FText::FromString(character->GetName()));

	if (character->GetStatComponent())
	{
		character->GetStatComponent()->_hpChanged.AddUObject(this, &UPartySlotUI::SetHpBarValue);
	}
	// ¾ÆÀÌÄÜ
}

void UPartySlotUI::SetHpBarValue(float ratio)
{
	HPBar->SetPercent(ratio);
	UE_LOG(LogTemp, Warning, TEXT("Character has been Damaged"));
}