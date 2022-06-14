// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

void UHudWidget::ChangeText(FText text)
{
	if (!RoleTextBlock)
	{
		return;
	}
	RoleTextBlock->SetText(text);
}