// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenButton.h"

#include "InvenUI.h"

void UInvenButton::SetButtonIndex()
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
