// Fill out your copyright notice in the Description page of Project Settings.


#include "Cable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACable::ACable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
}

// Called when the game starts or when spawned
void ACable::BeginPlay()
{

	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ACable::PickedUp);
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACable::BeginPlay()  World == nullptr"));
		return;
	}
	PlayerController = UGameplayStatics::GetPlayerController(World, 0);
}

// Called every frame
void ACable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsHeld) 
	{
		float CurrentMousePositonX;
		float CurrentMousePositonZ;
		PlayerController->GetMousePosition(CurrentMousePositonX, CurrentMousePositonZ);
		float DeltaX = CurrentMousePositonX - LastMousePositionX;
		float DeltaY = CurrentMousePositonZ - LastMousePositionZ;
		SetActorLocation(FVector(GetActorLocation().X - DeltaX, GetActorLocation().Y - DeltaY, GetActorLocation().Z ));
		LastMousePositionX = CurrentMousePositonX;
		LastMousePositionZ = CurrentMousePositonZ;
	}
}

void ACable::PickedUp(AActor* TouchedActor, FKey Key)
{
	bIsHeld = true;
	PlayerController->GetMousePosition(LastMousePositionX, LastMousePositionZ);
}


