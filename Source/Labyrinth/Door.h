// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class ARoomPathPoint;

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
	void DoorOpen(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void CloseDoor(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float DoorOpenCloseSpeed = 10.0f;
	bool bDoorOpening = false;
	bool bDoorClosing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDoorOpen = false;
	bool bDoorClose = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool bStartDoor = false;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool bEndDoor = false;

	// ** Set in blueprints for every door instance (need to make AI go to room with open door)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	ARoomPathPoint* Room1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	ARoomPathPoint* Room2;

private:
	float DoorClosedRoll;
	float DoorOpenedRoll;
	float DoorCurrentRoll;

};
