// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenButton.h"

#include "InvenUI.h"
#include "ShopUI.h"

void UInvenButton::SetInvenIndex()
{
	if (_widget == nullptr)
		return;

	auto widget = Cast<UInvenUI>(_widget);
	if (widget)
	{
		widget->_curIndex = _buttonIndex;
		return;
	}
}

void UInvenButton::SetShop_ShopIndex()
{
	if (_widget == nullptr)
		return;

	auto widget = Cast<UShopUI>(_widget);
	if (widget)
	{
		widget->_curShopIndex = _buttonIndex;
		return;
	}
}

void UInvenButton::SetShop_InvenIndex()
{
	if (_widget == nullptr)
		return;

	auto widget = Cast<UShopUI>(_widget);
	if (widget)
	{
		widget->_curInvenIndex = _buttonIndex;
		return;
	}
}
