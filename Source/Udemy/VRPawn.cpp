// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "Blueprint/UserWidget.h"



// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SuperMesh->SetupAttachment(Camera);

	Overhead = CreateDefaultSubobject<UWidgetComponent>(TEXT("Overhead"));
	Overhead->SetWidgetClass(HudWidgetRef);
	Overhead->SetupAttachment(VRRoot);

	bReplicates = true;
}

void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MovementDirection.IsZero())
	{
		Server_Move(MovementDirection, DeltaTime);
	}
	if (GEngine)
	{
		FName role = UEnum::GetValueAsName(GetLocalRole());
		FString printText = role.ToString();
		GEngine->AddOnScreenDebugMessage(2, DeltaTime, FColor::Cyan, printText);
	}

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
	PlayerInputComponent->BindAxis("RXJoycon", this, &AVRPawn::XMove);
	PlayerInputComponent->BindAxis("RYJoycon", this, &AVRPawn::YMove);
} 

void AVRPawn::XMove(float Value)
{
	MovementDirection.Y = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AVRPawn::YMove(float Value)
{
	MovementDirection.X = FMath::Clamp(Value, -1.0f, 1.0f);
}

FText AVRPawn::GetPlayerRole()
{
	if (HasAuthority()) {
		FName role = UEnum::GetValueAsName(GetRemoteRole());
		return FText::FromName(role);
	}
	else {
		FName role = UEnum::GetValueAsName(GetLocalRole());
		return FText::FromName(role);
	}
}

//RPC FUNCTIONS
void AVRPawn::Server_Move_Implementation(FVector MDirection, float DeltaTime)
{
	FRotator cameraOffset = Camera->GetForwardVector().Rotation();
	NewDirection.X = (MDirection.X * FMath::Cos(FMath::DegreesToRadians(cameraOffset.Yaw))) - (MDirection.Y * FMath::Sin(FMath::DegreesToRadians(cameraOffset.Yaw)));
	NewDirection.Y = MDirection.X * FMath::Sin(FMath::DegreesToRadians(cameraOffset.Yaw)) + MDirection.Y * FMath::Cos(FMath::DegreesToRadians(cameraOffset.Yaw));

	//const FVector NewLocation = GetActorLocation() + (NewDirection * DeltaTime * MovementSpeed);
	NewLocation = K2_GetActorLocation() + (NewDirection * DeltaTime * 500.0f);

	Multicast_Move(NewLocation);
}

void AVRPawn::Multicast_Move_Implementation(FVector NextLocation)
{
	SetActorLocation(NextLocation);
}