// Fill out your copyright notice in the Description page of Project Settings.


#include "HpBar.h"

#include "Components/ProgressBar.h"

void UHpBar::SetHpBarValue(float ratio)
{
	PB_HpBar->SetPercent(ratio);
}
