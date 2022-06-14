// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void ChangeText(FText text);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RoleTextBlock;

};