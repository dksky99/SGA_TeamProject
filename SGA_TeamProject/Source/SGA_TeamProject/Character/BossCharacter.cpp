// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"

#include "DamageLoggingComponent.h"
#include "../UI/DamageLoggingUI.h"

void ABossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_damageLogClass)
	{
		_damageLogWidget = CreateWidget<UDamageLoggingUI>(GetWorld(), _damageLogClass);
	}
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	_dmgLogComponent->_dmgLogChanged.AddUObject(this, &ABossCharacter::DamageLogUpdate);

	if (_damageLogWidget)
	{
		_damageLogWidget->AddToViewport();
	}
}

void ABossCharacter::DamageLogUpdate()
{
	if (_damageLogWidget && _dmgLogComponent)
	{
		auto damageList = _dmgLogComponent->GetValidList();
		auto damageLogWidget = Cast<UDamageLoggingUI>(_damageLogWidget);
		if (damageLogWidget)
		{
			damageLogWidget->UpdateList(damageList);
		}
	}

}
