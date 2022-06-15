// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHudWidget::ChangeText(FText text)
{
	if (!RoleTextBlock)
	{
		return;
	}
	RoleTextBlock->SetText(text);
}

FText UHudWidget::GetText()
{
	if (!RoleTextBlock)
	{
		return FText::FromString("Failed");
	}
	return RoleTextBlock->GetText();
}