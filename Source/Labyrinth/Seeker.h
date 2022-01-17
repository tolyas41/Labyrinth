// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Seeker.generated.h"

class ARoomTrigger;
class ADoor;

UCLASS()
class LABYRINTH_API ASeeker : public ACharacter
{
	GENERATED_BODY()

public:
	ASeeker();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OpenRandomDoor();

	ARoomTrigger* TriggerRoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ADoor* OpeningDoor;

	//use in BT to prevent patrolling
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isGoingToRoom;

	//Location of two rooms with one randomly opened door
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Room1Loc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Room2Loc;
};
