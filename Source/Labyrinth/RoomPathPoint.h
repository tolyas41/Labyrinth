// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomPathPoint.generated.h"

UCLASS()
class LABYRINTH_API ARoomPathPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoomPathPoint();

protected:
	virtual void BeginPlay() override;


};
