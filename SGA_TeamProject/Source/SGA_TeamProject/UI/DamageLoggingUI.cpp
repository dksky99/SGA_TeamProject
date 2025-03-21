// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageLoggingUI.h"

#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

#include "../Character/CharacterBase.h"

void UDamageLoggingUI::UpdateList(TArray<TPair<class ACharacterBase*, int32>> damageArray)
{
	List->ClearChildren();

	for (const auto& entry : damageArray)
	{
		auto textBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		if (textBlock)
		{
			FString text = FString::Printf(TEXT("%s : %d"), *entry.Key->GetName(), entry.Value);
			textBlock->SetText(FText::FromString(text));

			List->AddChild(textBlock);
		}
	}
}
