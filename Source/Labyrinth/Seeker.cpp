// Fill out your copyright notice in the Description page of Project Settings.


#include "Seeker.h"

ASeeker::ASeeker()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASeeker::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASeeker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASeeker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

