// Fill out your copyright notice in the Description page of Project Settings.


#include "Overworld/Actors/Building.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SwitchCount = FMath::RandRange(0, 3);
	RouterCount = FMath::RandRange(0, 3);
	DecoderCount = FMath::RandRange(0, 3);

	if (!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Static Mesh Component"));
		
		for (int i = 1;i <= 3;i++)
		{
			FString MatPath = FString::Printf(TEXT("UMaterial'/Game/Assets/Materials/Building%dMaterial.Building%dMaterial'"), i, i);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *MatPath);
			ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(*MatPath);
			PossibleMaterials.Add(MaterialAsset.Object);
		}
	}
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();	
	if (!StaticMeshComponent) return;
	int RandomIndex = FMath::RandRange(0, 2);
	UE_LOG(LogTemp, Warning, TEXT("TThis is randim id: %d"), RandomIndex);
	StaticMeshComponent->SetMaterial(0, PossibleMaterials[RandomIndex]);
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

