// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabyrinthCharacter.h"
#include "LabyrinthPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"
#include "RoomTrigger.h"
#include "Seeker.h"

ALabyrinthCharacter::ALabyrinthCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

	DoorOpenBoundsChecker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorOpenBoundsChecker"));
	DoorOpenBoundsChecker->SetupAttachment(RootComponent);
}

void ALabyrinthCharacter::BeginPlay()
{
	Super::BeginPlay();

	DoorOpenBoundsChecker->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	DoorOpenBoundsChecker->OnComponentBeginOverlap.AddDynamic(this, &ALabyrinthCharacter::OnOverlapBegin);
	DoorOpenBoundsChecker->OnComponentEndOverlap.AddDynamic(this, &ALabyrinthCharacter::OnOverlapEnd);
	Seeker = Cast<ASeeker>(UGameplayStatics::GetActorOfClass(GetWorld(), ASeeker::StaticClass()));
	TriggerRoom = nullptr;
	DoorToOpen = nullptr;
	RandomDoor = nullptr;
	//GetWorldTimerManager().SetTimer(RandomDoorTimerHandle, this, &ALabyrinthCharacter::OpenRandomDoor, OpenRandomDoorCooldown, true);

}

//void ALabyrinthCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ALabyrinthCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALabyrinthCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALabyrinthCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALabyrinthCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALabyrinthCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("OpenDoor", IE_Pressed, this, &ALabyrinthCharacter::OpenDoor);
	PlayerInputComponent->BindAction("OpenDoor", IE_Released, this, &ALabyrinthCharacter::ResetTimer);
}

void ALabyrinthCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALabyrinthCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALabyrinthCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALabyrinthCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ALabyrinthCharacter::OpenDoor_Implementation()
{
	if (RandomDoor)
	{
		DoorToOpen = RandomDoor;
	}
	if (DoorToOpen && DoorToOpen->bDoorClose && !DoorToOpen->bStartDoor)
	{
		if (DoorToOpen->bEndDoor)
		{
			//TODO WIN
		}
		for (ADoor* door : TriggerRoom->Doors)
		{
			door->bDoorClosing = true;
			door->bDoorOpening = false;
		}
		DoorToOpen->bDoorOpening = true;
		DoorToOpen->bDoorClosing = false;

		//Open a door in AI room if DoorToOpen doesnt lead to AI room
		bool bConnectedRooms = false;
		for (ADoor* door : Seeker->TriggerRoom->Doors)
		{
			if (DoorToOpen == door)
			{
				bConnectedRooms = true;
			}
		}
		if (!bConnectedRooms)
		{
			Seeker->OpenRandomDoor();
		}
	}
}

void ALabyrinthCharacter::OpenRandomDoor()
{
	if (TriggerRoom)
	{
		size_t OpenRandomDoorID = FMath::RandRange(0, TriggerRoom->Doors.Num() - 1);
		RandomDoor = TriggerRoom->Doors[OpenRandomDoorID];
		OpenDoor();
		RandomDoor = nullptr;
	}
}

void ALabyrinthCharacter::ResetTimer()
{
	if (DoorToOpen)
	{
		Cast<ALabyrinthPlayerController>(GetController())->SetDoorTimer();
	}
}

void ALabyrinthCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADoor>(OtherActor))
	{
		DoorToOpen = Cast<ADoor>(OtherActor);
	}
}

void ALabyrinthCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ADoor>(OtherActor))
	{
		DoorToOpen = nullptr;
	}
}

