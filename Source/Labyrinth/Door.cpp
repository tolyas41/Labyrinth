// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

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
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDoorOpening)
	{
		DoorOpen(DeltaTime);
	}
	if (bDoorClosing)
	{
		CloseDoor(DeltaTime);
	}
}

void ADoor::DoorOpen(float DeltaTime)
{
	DoorCurrentYaw = FMath::Lerp(DoorCurrentYaw, DoorOpenedYaw, DoorOpenCloseSpeed);
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

//void ADoor::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(ADoor, bDoorOpening);
//}

//void ADoor::OnRep_DoorOpening(bool b)
//{
//	OpenDoor(0.01f);
//}

void ADoor::OpenDoorFunc_Implementation()
{
	bDoorOpening = true;
}
