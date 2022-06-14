// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Saving/PainterSaveGame.h"


// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (PaintBrushHandControllerClass)
	{
		RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		RightPaintBrushHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightPaintBrushHandController->SetOwner(this);
	}

}


void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("RAPress"), EInputEvent::IE_Pressed, this, &AVRPawn::Save);
	PlayerInputComponent->BindAction(TEXT("RBPress"), EInputEvent::IE_Pressed, this, &AVRPawn::Load);

} 

void AVRPawn::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	Painting->SetState("Hello World");
	Painting->Save();
}

void AVRPawn::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load();
	if (Painting)
	{
		UE_LOG(LogTemp, Warning, TEXT("Number of times Saved: %s"), *Painting->GetState());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Not Found"));
	}

}