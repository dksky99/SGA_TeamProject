// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipItem.h"

void AEquipItem::UseItem(APlayerCharacter* player)
{
	if (player->IsAlive())
	{
		player->AddAtk(GetData().atk);
		player->AddMaxHp(GetData().hp);
		player->AddHp(GetData().hp);
		player->AddSpeed(GetData().speed);
	}
}

void AEquipItem::RemoveItem(APlayerCharacter* player)
{
	if (player->IsAlive())
	{
		player->AddAtk(GetData().atk * -1);
		player->AddMaxHp(GetData().hp * -1);
		player->AddHp(GetData().hp * -1);
		player->AddSpeed(GetData().speed * -1);
	}
}
