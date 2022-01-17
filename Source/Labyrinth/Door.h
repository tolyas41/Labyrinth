// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class ARoomPathPoint;
class UTimelineComponent;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorTimelineFloatCurve;
	FOnTimelineFloat UpdateFunctionFloat;

	UPROPERTY(EditAnywhere)
	float DoorOpenCloseSpeed = 10.0f;
	bool bDoorOpening = false;
	bool bDoorClosing = false;
	bool bDoorOpen = false;
	bool bDoorClose = true;

	// ** Set in blueprints for every door instance (need to make AI go to room with open door)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	ARoomPathPoint* Room1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	ARoomPathPoint* Room2;

	UFUNCTION(NetMulticast, unreliable)
	void DoorOpen(float DeltaTime);
	UFUNCTION(BlueprintCallable, NetMulticast, unreliable)
	void CloseDoor(float DeltaTime);
	UFUNCTION()
	void UpdateTimelineComp(float Output);

private:
	float DoorClosedRoll;
	float DoorOpenedRoll;
	float DoorCurrentRoll;

};
