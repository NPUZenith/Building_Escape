// Copyright Maanav Rao 202


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	/*UE_LOG(LogTemp, Warning, TEXT("%f"), GetOwner()->GetActorRotation().Yaw);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());*/
	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the Open Door component on it, but no pressure plate set!"), *GetOwner()->GetName())
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
	}
	else
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator DoorRotation;
	DoorRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 1.f);
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator DoorRotation;
	DoorRotation.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 1.f);
	GetOwner()->SetActorRotation(DoorRotation);
}
