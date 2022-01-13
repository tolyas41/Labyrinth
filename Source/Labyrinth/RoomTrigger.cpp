// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTrigger.h"
#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "LabyrinthCharacter.h"
#include "Seeker.h"

void ARoomTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &ARoomTrigger::OnOverlapBegin);
	//OnActorEndOverlap.AddDynamic(this, &ARoomTrigger::OnOverlapEnd);
}

void ARoomTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	ALabyrinthCharacter* Character = Cast<ALabyrinthCharacter>(OtherActor);
	if (Character)
	{
		Character->TriggerRoom = this;
	}
	ASeeker* Seeker = Cast<ASeeker>(OtherActor);
	if (Seeker)
	{
		Seeker->TriggerRoom = this;
	}
}

//void ARoomTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
//{
//}
