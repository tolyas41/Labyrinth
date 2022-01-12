// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;

UCLASS()
class LABYRINTH_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	//UFUNCTION(NetMulticast, Unreliable)
	UFUNCTION()
	void DoorOpen(float DeltaTime);
	UFUNCTION()
	void CloseDoor(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float DoorOpenCloseSpeed = 10.0f;
	//UPROPERTY(Replicated)
	bool bDoorOpening = false;
	bool bDoorClosing = false;
	//UFUNCTION(NetMulticast, reliable)
	//void OpenDoorFunc();

	//void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//UFUNCTION()
	//void OnRep_DoorOpening(bool b);

private:
	float DoorClosedRoll;
	float DoorOpenedRoll;
	float DoorCurrentRoll;

};
