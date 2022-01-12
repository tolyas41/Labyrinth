// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTrigger.h"
#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "LabyrinthCharacter.h"

//ARoomTrigger::ARoomTrigger()
//{
//}

void ARoomTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &ARoomTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ARoomTrigger::OnOverlapEnd);
}

void ARoomTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	ALabyrinthCharacter* Character = Cast<ALabyrinthCharacter>(OtherActor);
	if (Character)
	{
		Character->TriggerRoom = this;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Character->GetName());

	}
}

void ARoomTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	ALabyrinthCharacter* Character = Cast<ALabyrinthCharacter>(OtherActor);
	if (Character)
	{
		Character->TriggerRoom = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Character->GetName());

	}
}
