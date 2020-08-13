// Copyright Maanav Rao 202


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	UE_LOG(LogTemp, Warning, TEXT("%f"), GetOwner()->GetActorRotation().Yaw);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw = InitialYaw + 90.f;

	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator DoorRotation;
	DoorRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.f);
	GetOwner()->SetActorRotation(DoorRotation);
	// ...
}

