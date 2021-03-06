// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"

#include "Camera/CameraComponent.h"
#include "HandControllerBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "HudWidget.h"

#include "VRPawn.generated.h"

UCLASS()
class UDEMY_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();
	
	//RPC FUNCTIONS
	UFUNCTION()
	void Client_Move(FVector MDirection, float DeltaTime);

	UFUNCTION(Server, Reliable)
	void Server_Move(FVector NextLocation);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Move(FVector NextLocation);

	UFUNCTION(BlueprintCallable)
	FText GetPlayerRole();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* Overhead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaTime) override;

private:
	void RightTriggerPressed()
	{
		if (RightPaintBrushHandController) RightPaintBrushHandController->TriggerPressed();
	}

	void RightTriggerReleased()
	{
		if (RightPaintBrushHandController) RightPaintBrushHandController->TriggerReleased();
	}
	
	void XMove(float Value);
	void YMove(float Value);

	//Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> PaintBrushHandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SuperMesh;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 500.0f;

	//Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* VRRoot;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;


	//References
	UPROPERTY()
	AHandControllerBase* RightPaintBrushHandController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HudWidgetRef;
	

	FVector MovementDirection;
	FVector NewDirection;
	FVector NewLocation;
};
