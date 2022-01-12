// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RoomTrigger.generated.h"

//class UStaticMeshComponent;
class ADoor;

UCLASS()
class LABYRINTH_API ARoomTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	//ARoomTrigger();
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	//UPROPERTY(EditAnywhere)
	//UStaticMeshComponent* StaticMesh;

	// ** Doors set in blueprints for every room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors")
	TArray<ADoor*> Doors;

//protected:
//	virtual void BeginPlay() override;

};
