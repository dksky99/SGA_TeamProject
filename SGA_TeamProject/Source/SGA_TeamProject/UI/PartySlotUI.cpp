// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySlotUI.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Character/CharacterBase.h"
#include "../Character/StatComponent.h"

void UPartySlotUI::Setup(ACharacterBase* character)
{
	if (!character)
		return;

	_character = character;
	Name->SetText(character->GetCharacterName());

	if (character->GetStatComponent())
	{
		character->GetStatComponent()->_hpChanged.AddUObject(this, &UPartySlotUI::SetHpBarValue);
	}
}

void UPartySlotUI::UpdateSlot(bool isPlayer)
{
	if (isPlayer)
	{
		Icon->SetBrushFromTexture(_playerTexture);
	}
	else
	{
		Icon->SetBrushFromTexture(_defaultTexture);
	}
}

void UPartySlotUI::SetHpBarValue(float ratio)
{
	HPBar->SetPercent(ratio);
}