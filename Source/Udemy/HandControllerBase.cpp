// Fill out your copyright notice in the Description page of Project Settings.


#include "HandControllerBase.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

// Sets default values
AHandControllerBase::AHandControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);

	bReplicates = true;

	ControllerNetUpdateRate = 100.0f;
	ControllerNetUpdateCount = 0.0f;
	/*
	FName role = UEnum::GetValueAsName(GetLocalRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s"), *role.ToString());
	*/
	

}

void AHandControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsServer = IsServer();

	if (bHasAuthority)
	{
		ReplicatedControllerTransform = GetActorTransform();
	}
}

void AHandControllerBase::TriggerPressed() {}

void AHandControllerBase::TriggerReleased() {}

void AHandControllerBase::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AHandControllerBase, ReplicatedControllerTransform, COND_SkipOwner);

}

void AHandControllerBase::Server_SendControllerTransform_Implementation(FTransform NewTransform)
{
	// Store new transform and trigger OnRep_Function
	ReplicatedControllerTransform = NewTransform;

	// Server should no longer call this RPC itself, but if is using non tracked then it will so keeping auth check
	if (!bHasAuthority)
		OnRep_ReplicatedControllerTransform();
}