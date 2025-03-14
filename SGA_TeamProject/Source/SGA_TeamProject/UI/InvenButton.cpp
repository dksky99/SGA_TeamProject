// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenButton.h"

#include "InvenUI.h"

void UInvenButton::SetButtonIndex()
{
	if (_invenUI == nullptr)
		return;

	_invenUI->_curIndex = _buttonIndex;
}
