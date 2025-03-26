// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"

#include "../Character/PlayerCharacter.h"

APotion::APotion()
{
}

void APotion::UseItem(APlayerCharacter* player)
{
	player->AddHp(10);
}
