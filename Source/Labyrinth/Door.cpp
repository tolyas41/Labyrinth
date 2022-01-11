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

	if (!bDoorOpen)
	{
		OpenDoor(DeltaTime);
	}
}

void ADoor::OpenDoor(float DeltaTime)
{
	//FVector OpenDirection = GetActorRightVector() * DeltaTime * 20.0f;
	//AddActorLocalOffset(OpenDirection);
	//AddActorLocalRotation(FRotator(0.0f, 20.0f * DeltaTime, 0.0f));
	//if (GetActorLocation() >= InitalLocation + GetActorForwardVector() * DoorWidth)

	DoorCurrentYaw = FMath::Lerp(DoorCurrentYaw, DoorOpenedYaw, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Yaw = DoorCurrentYaw;
	SetActorRotation(DoorRotation);
	if (DoorCurrentYaw == DoorOpenedYaw)
	{
		bDoorOpen = true;
	}
}
