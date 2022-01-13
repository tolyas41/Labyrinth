// Fill out your copyright notice in the Description page of Project Settings.


#include "Seeker.h"
#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "LabyrinthGameMode.h"
#include "RoomTrigger.h"
#include "RoomPathPoint.h"

ASeeker::ASeeker()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASeeker::BeginPlay()
{
	Super::BeginPlay();

	Room1Loc = GetActorLocation();
	Room2Loc = GetActorLocation();
}

void ASeeker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASeeker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASeeker::OpenRandomDoor()
{
	size_t OpenDoorID = FMath::RandRange(0, TriggerRoom->Doors.Num());

	for (size_t i = 0; i < TriggerRoom->Doors.Num(); i++)
	{
		if (i == OpenDoorID)
		{
			TriggerRoom->Doors[i]->bDoorOpening = true;
			TriggerRoom->Doors[i]->bDoorClosing = false;
			Room1Loc = TriggerRoom->Doors[i]->Room1->GetActorLocation();
			Room2Loc = TriggerRoom->Doors[i]->Room2->GetActorLocation();
		}
		else
		{
			TriggerRoom->Doors[i]->bDoorClosing = true;
			TriggerRoom->Doors[i]->bDoorOpening = false;
		}
	}
}
