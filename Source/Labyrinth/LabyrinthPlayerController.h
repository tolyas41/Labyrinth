// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LabyrinthPlayerController.generated.h"

class ALabyrinthCharacter;

UCLASS()
class LABYRINTH_API ALabyrinthPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetDoorTimer();
	void OpenRandomDoor();

	ALabyrinthCharacter* LabPlayer;
	FTimerHandle RandomDoorTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpenRandomDoorCooldown = 30.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TimeToOpenRandomDoor;

};
