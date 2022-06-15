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
	AHandControllerBase::SetReplicateMovement(true);
}

void AHandControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHandControllerBase::TriggerPressed() {}

void AHandControllerBase::TriggerReleased() {}

void AHandControllerBase::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME_CONDITION(AHandControllerBase, ReplicatedMovement, COND_SimulatedOnly);

}

/*
void AHandControllerBase::Server_SendControllerTransform_Implementation(FTransform NewTransform)
{
	// Store new transform and trigger OnRep_Function
	ReplicatedControllerTransform = NewTransform;

	// Server should no longer call this RPC itself, but if is using non tracked then it will so keeping auth check
	if (!bHasAuthority)
		OnRep_ReplicatedControllerTransform();
}
*/