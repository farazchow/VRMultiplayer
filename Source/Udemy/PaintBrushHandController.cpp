// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintBrushHandController.h"
#include "Math/Vector.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

// Sets default values
APaintBrushHandController::APaintBrushHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void APaintBrushHandController::TriggerPressed()
{
	AStroke* Stroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
	Stroke->SetActorLocation(GetActorLocation()); 
}

void APaintBrushHandController::TriggerReleased()
{
}

