// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "Components/SceneComponent.h"
#include "HandControllerBase.generated.h"

UCLASS()
class UDEMY_API AHandControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandControllerBase();
	virtual void TriggerPressed();
	virtual void TriggerReleased();

	
	//Controller Replication
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ReplicatedControllerTransform)
	FTransform ReplicatedControllerTransform;

	UFUNCTION()
	virtual void OnRep_ReplicatedControllerTransform()
	{
		if (!IsLocallyControlled())
		{
			SetActorRelativeTransform(ReplicatedControllerTransform);

		}
	}

	UFUNCTION(Server, Unreliable)
	void Server_SendControllerTransform(FTransform NewTransform);
	


	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	
	UFUNCTION()
	void ChooseTracking(EControllerHand hand);

private:
	//Components
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* MotionController;

	bool bHasAuthority;

protected:
	virtual void Tick(float DeltaTime) override;

	bool IsServer() const
	{
		if (GEngine && GWorld)
		{
			if (GEngine->GetNetMode(GWorld) == NM_Client) { return false; }
			else { return true; }
		}
		return false;
	}

	virtual void BeginPlay() override;

	bool IsLocallyControlled() const
	{
		const AActor* MyOwner = GetOwner();
		return MyOwner->HasLocalNetOwner();
	}
};
