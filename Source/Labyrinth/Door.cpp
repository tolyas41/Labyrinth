// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = StaticMesh;

}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	DoorClosedYaw = GetActorRotation().Yaw;
	DoorOpenedYaw = DoorClosedYaw + 90.0f;
	//DoorWidth = StaticMesh->CalcBounds()
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorLocalRotation(FRotator(0.0f, 1.0f, 0.0f)); WORK

	if (bDoorOpening)
	{
		OpenDoor(DeltaTime);
	}
	if (bDoorClosing)
	{
		CloseDoor(DeltaTime);
	}
}

void ADoor::OpenDoor(float DeltaTime)
{
	DoorCurrentYaw = FMath::Lerp(DoorCurrentYaw, DoorOpenedYaw, DeltaTime * DoorOpenCloseSpeed);
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Yaw = DoorCurrentYaw;
	SetActorRotation(DoorRotation);
	if (FMath::IsNearlyEqual(DoorCurrentYaw, DoorOpenedYaw, 0.5f))
	{
		bDoorOpening = false;
	}
}

void ADoor::CloseDoor(float DeltaTime)
{
	DoorCurrentYaw = FMath::Lerp(DoorCurrentYaw, DoorClosedYaw, DeltaTime * DoorOpenCloseSpeed);
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Yaw = DoorCurrentYaw;
	SetActorRotation(DoorRotation);
	if (FMath::IsNearlyEqual(DoorCurrentYaw, DoorClosedYaw, 0.5f))
	{
		bDoorClosing = false;
	}
}
