// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPointerHandController.h"

AUIPointerHandController::AUIPointerHandController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Pointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Pointer"));
	Pointer->SetupAttachment(GetRootComponent());
	Pointer->bShowDebug = true;
}

 
void AUIPointerHandController::TriggerPressed()
{
	Pointer->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::TriggerReleased()
{
	Pointer->ReleasePointerKey(EKeys::LeftMouseButton);
}