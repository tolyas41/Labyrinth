// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/TimelineComponent.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = StaticMesh;
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	//DoorClosedRoll = GetActorRotation().Roll;
	//DoorOpenedRoll = DoorClosedRoll + 90.0f;

	UpdateFunctionFloat.BindDynamic(this, &ADoor::UpdateTimelineComp);

	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (bDoorOpening)
	//{
	//	DoorOpen(DeltaTime);
	//}
	//if (bDoorClosing)
	//{
	//	CloseDoor(DeltaTime);
	//}
}

void ADoor::OpenDoor_Implementation()
{
	DoorTimelineComp->Play();
	bDoorOpen = true;
	bDoorClose = false;

	//DoorCurrentRoll = FMath::Lerp(DoorCurrentRoll, DoorOpenedRoll, DeltaTime * DoorOpenCloseSpeed);
	//FRotator DoorRotation = GetActorRotation();
	//DoorRotation.Roll = DoorCurrentRoll;
	//SetActorRotation(DoorRotation);
	//if (FMath::IsNearlyEqual(DoorCurrentRoll, DoorOpenedRoll, 0.05f))
	//{
	//	bDoorOpening = false;
	//	bDoorOpen = true;
	//}
}

void ADoor::CloseDoor_Implementation()
{
	DoorTimelineComp->Reverse();
	bDoorClose = true;
	bDoorOpen = false;

	//DoorCurrentRoll = FMath::Lerp(DoorCurrentRoll, DoorClosedRoll, DeltaTime * DoorOpenCloseSpeed);
	//FRotator DoorRotation = GetActorRotation();
	//DoorRotation.Roll = DoorCurrentRoll;
	//SetActorRotation(DoorRotation);
	//if (FMath::IsNearlyEqual(DoorCurrentRoll, DoorClosedRoll, 0.05f))
	//{
	//	bDoorClosing = false;
	//	bDoorClose = true;
	//}
}

void ADoor::UpdateTimelineComp(float Output)
{
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Roll = Output;
	//FRotator DoorNewRotation = FRotator(0.0f, 0.0f, Output);
	StaticMesh->SetRelativeRotation(DoorRotation);
}