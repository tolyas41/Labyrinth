// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Seeker.generated.h"

class ARoomTrigger;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Room1Loc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Room2Loc;
};
