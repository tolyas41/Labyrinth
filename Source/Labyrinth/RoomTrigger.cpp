// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTrigger.h"
#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "LabyrinthCharacter.h"

ARoomTrigger::ARoomTrigger()
{
	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Room Mesh"));
	//RootComponent = StaticMesh;
	//StaticMesh->SetVisibility(false);
}

void ARoomTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &ARoomTrigger::OnOverlapBegin);
}

//void ARoomTrigger::BeginPlay()
//{
//	Super::BeginPlay();
//	//StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ARoomTrigger::OnOverlapBegin);
//	//(FActorBeginOverlapSignature, AActor, OnActorBeginOverlap, AActor*, OverlappedActor, AActor*, OtherActor);
//
//	//GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARoomTrigger::OnOverlapBegin);
//}

void ARoomTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	//ADoor* DoorInRoom = Cast<ADoor>(OtherActor);
	//if (DoorInRoom)
	//{
	//	Doors.Add(DoorInRoom);
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *DoorInRoom->GetName());

	//}
	for (ADoor* door : Doors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *door->GetName());
	}

	ALabyrinthCharacter* Character = Cast<ALabyrinthCharacter>(OtherActor);
	if (Character)
	{
		Character->TriggerRoom = this;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Character->GetName());

	}
}
