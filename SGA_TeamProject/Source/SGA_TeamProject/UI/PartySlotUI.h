// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartySlotUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UPartySlotUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(class ACharacterBase* character);
	void UpdateSlot(bool isPlayer);

	void SetHpBarValue(float ratio);

	class ACharacterBase* GetCharacter() { return _character; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HPBar;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _defaultTexture;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* _playerTexture;

	class ACharacterBase* _character;
};
