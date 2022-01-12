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
	DoorClosedRoll = GetActorRotation().Roll;
	DoorOpenedRoll = DoorClosedRoll + 90.0f;
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
	DoorCurrentRoll = FMath::Lerp(DoorCurrentRoll, DoorOpenedRoll, DeltaTime * DoorOpenCloseSpeed);
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Roll = DoorCurrentRoll;
	SetActorRotation(DoorRotation);
	if (FMath::IsNearlyEqual(DoorCurrentRoll, DoorOpenedRoll, 0.05f))
	{
		bDoorOpening = false;
	}
}

void ADoor::CloseDoor(float DeltaTime)
{
	DoorCurrentRoll = FMath::Lerp(DoorCurrentRoll, DoorClosedRoll, DeltaTime * DoorOpenCloseSpeed);
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Roll = DoorCurrentRoll;
	SetActorRotation(DoorRotation);
	if (FMath::IsNearlyEqual(DoorCurrentRoll, DoorClosedRoll, 0.05f))
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

//void ADoor::OpenDoorFunc_Implementation()
//{
//	bDoorOpening = true;
//}
