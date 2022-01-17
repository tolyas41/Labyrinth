// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* DoorTimelineFloatCurve;
	FOnTimelineFloat UpdateFunctionFloat;
	FOnTimelineEvent OnFinishedCallback;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bDoorOpen = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bDoorClose = true;

	// ** Set in blueprints for every door instance (need to make AI go to room with open door)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	ARoomPathPoint* Room1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	ARoomPathPoint* Room2;

	UFUNCTION(NetMulticast, unreliable)
	void OpenDoor();
	UFUNCTION(BlueprintCallable, NetMulticast, unreliable)
	void CloseDoor();
	UFUNCTION()
	void UpdateTimelineComp(float Output);
	UFUNCTION()
	void OnTimelineFinished();

};
