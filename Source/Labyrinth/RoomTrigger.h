// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RoomTrigger.generated.h"

class ADoor;

UCLASS()
class LABYRINTH_API ARoomTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// ** Doors set in blueprints for every room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors")
	TArray<ADoor*> Doors;
};
