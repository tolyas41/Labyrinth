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

	OnFinishedCallback.BindUFunction(this, TEXT("OnTimelineFinished"));
	DoorTimelineComp->SetTimelineFinishedFunc(OnFinishedCallback);

	UpdateFunctionFloat.BindDynamic(this, &ADoor::UpdateTimelineComp);

	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OpenDoor_Implementation()
{
	DoorTimelineComp->Play();
}

void ADoor::CloseDoor_Implementation()
{
	DoorTimelineComp->Reverse();
}

void ADoor::UpdateTimelineComp(float Output)
{
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Roll = Output;
	StaticMesh->SetRelativeRotation(DoorRotation);
}

void ADoor::OnTimelineFinished()
{
	if (FMath::IsNearlyEqual(GetActorRotation().Roll, 90.0f, 0.1f))
	{
		bDoorOpen = true;
		bDoorClose = false;
	}
	if (FMath::IsNearlyEqual(GetActorRotation().Roll, 0.0f, 0.1f))
	{
		bDoorOpen = false;
		bDoorClose = true;
	}
}
