// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyListUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAMPROJECT_API UPartyListUI : public UUserWidget
{
	GENERATED_BODY()

public:
    void AddPartySlot(class ACharacterBase* character);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UVerticalBox* PartyList;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UPartySlotUI> _partySlotClass;
	
};
