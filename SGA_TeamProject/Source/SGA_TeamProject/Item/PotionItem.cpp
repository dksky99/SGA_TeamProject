// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionItem.h"


APotionItem::APotionItem()
{
}

void APotionItem::UseItem(APlayerCharacter* player)
{
	if (player->IsAlive())
		player->AddHp(GetData().heal);
}
