 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGame* Create();
	bool Save();
	static UPainterSaveGame* Load();

	void SetState(FString NewState) { State = NewState; }
	FString GetState() const { return State; }

	void incrementState() { TimesLoaded = TimesLoaded + 1; }
	FString GetInt() const { return FString::FromInt(TimesLoaded); }

private:
	//State
	UPROPERTY()
	int TimesLoaded = 0;

	UPROPERTY()
	FString State;
};
 