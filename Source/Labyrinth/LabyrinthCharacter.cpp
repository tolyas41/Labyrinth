// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabyrinthCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Door.h"

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
	//DoorOpenBoundsChecker->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//DoorOpenBoundsChecker->SetCollisionProfileName(UCollisionProfile::)


}

void ALabyrinthCharacter::BeginPlay()
{
	Super::BeginPlay();
	DoorOpenBoundsChecker->OnComponentBeginOverlap.AddDynamic(this, &ALabyrinthCharacter::OnOverlapBegin);
	DoorOpenBoundsChecker->OnComponentEndOverlap.AddDynamic(this, &ALabyrinthCharacter::OnOverlapEnd);
}

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

void ALabyrinthCharacter::OpenDoor()
{
	if (DoorToOpen)
	{
		DoorToOpen->bDoorOpening = true;
	}
}

void ALabyrinthCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoorToOpen = Cast<ADoor>(OtherActor);
}

void ALabyrinthCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	DoorToOpen = nullptr;
}
