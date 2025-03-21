// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "BossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API ABossCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	void DamageLogUpdate();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DamageLog", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _damageLogClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DamageLog", meta = (AllowPrivateAccess = "true"))
	class UUserWidget* _damageLogWidget;
};
