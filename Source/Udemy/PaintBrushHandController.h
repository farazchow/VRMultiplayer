// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.h"
#include "HandControllerBase.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class UDEMY_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintBrushHandController();

	void TriggerPressed() override;
	void TriggerReleased() override;

private:
	//Config
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStroke> StrokeClass;

	 
};
