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

	UFUNCTION()
	void OpenDoor(float DeltaTime);
	UFUNCTION()
	void CloseDoor(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float DoorOpenCloseSpeed = 10.0f;
	bool bDoorOpening = false;
	bool bDoorClosing = false;

private:
	float DoorClosedYaw;
	float DoorOpenedYaw;
	float DoorCurrentYaw;

};
