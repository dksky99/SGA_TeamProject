// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyListUI.h"
#include "PartySlotUI.h"
#include "Components/VerticalBox.h"

void UPartyListUI::AddPartySlot(ACharacterBase* character)
{
	if (!character)
		return;

	auto partySlot = CreateWidget<UPartySlotUI>(this, _partySlotClass);
	if (partySlot)
	{
		partySlot->Setup(character);
		PartyList->AddChild(partySlot);
	}
}

void UPartyListUI::UpdateList(ACharacterBase* character)
{
	for (auto widget : PartyList->GetAllChildren())
	{
		auto slot = Cast<UPartySlotUI>(widget);
		{
			slot->UpdateSlot(slot->GetCharacter() == character);
		}
	}
}
