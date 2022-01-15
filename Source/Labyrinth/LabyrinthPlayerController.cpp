// Fill out your copyright notice in the Description page of Project Settings.


#include "LabyrinthPlayerController.h"
#include "LabyrinthCharacter.h"

void ALabyrinthPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeToOpenRandomDoor = GetWorldTimerManager().GetTimerRemaining(RandomDoorTimerHandle);
}


void ALabyrinthPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetDoorTimer();
}

void ALabyrinthPlayerController::SetDoorTimer()
{
	GetWorldTimerManager().SetTimer(RandomDoorTimerHandle, this, &ALabyrinthPlayerController::OpenRandomDoor, OpenRandomDoorCooldown, true);
}

void ALabyrinthPlayerController::OpenRandomDoor()
{
	LabPlayer = Cast<ALabyrinthCharacter>(GetPawn());
	if (LabPlayer)
	{
		LabPlayer->OpenRandomDoor();
	}
}