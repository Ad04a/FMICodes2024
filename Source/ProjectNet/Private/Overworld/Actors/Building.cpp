// Fill out your copyright notice in the Description page of Project Settings.


#include "Overworld/Actors/Building.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/OverWorldGameModeBase.h"
#include "GameStates/NETGameState.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	IsConnected = false;
	SwitchCount = FMath::RandRange(0, 3);
	RouterCount = FMath::RandRange(0, 3);
	DecoderCount = FMath::RandRange(0, 3);

	if (!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Static Mesh Component"));
		
		for (int i = 0;i <= 13;i++)
		{
			FString MatPath = FString::Printf(TEXT("UMaterial'/Game/Assets/Materials/Building%dMaterial.Building%dMaterial'"), i, i);
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

	int RandomIndex = FMath::RandRange(0, 12);
	ANETGameState* GameState = (ANETGameState*)GetWorld()->GetGameState();
	if (!IsValid(GameState)) return;
	GameState->SpawnedBuildingsCount++;
	if (!GameState->IsCentralSpawned && GameState->SpawnedBuildingsCount>45)
	{
		GameState->IsCentralSpawned = true;
		IsCentral = true;
		IsInteractable = true;
		IsConnected = true;
		StaticMeshComponent->SetMaterial(0, PossibleMaterials[0]);
		return;
	}
	if (RandomIndex == 0) RandomIndex = FMath::RandRange(1, 12);
	IsInteractable = RandomIndex < 7;
	UE_LOG(LogTemp, Warning, TEXT("TThis is randim id: %d"), RandomIndex);
	StaticMeshComponent->SetMaterial(0, PossibleMaterials[RandomIndex]);
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::DrawLine()
{
	UE_LOG(LogTemp, Warning, TEXT("1?"))
	if (AOverWorldGameModeBase* GameMode = (AOverWorldGameModeBase*)UGameplayStatics::GetGameMode(GetWorld()))
	{
		UE_LOG(LogTemp, Warning, TEXT("2?"))
		if (GameMode->IsConnecting)
		{
			UE_LOG(LogTemp, Warning, TEXT("3?"))
			if (GameMode->FirstBuildingRef == this)
			{
				GameMode->IsConnecting = false;
				return;
			}
			UE_LOG(LogTemp, Warning, TEXT("connecting true, spawning?"));
			FVector Loc1 = this->GetTransform().GetLocation(), Loc2 = GameMode->FirstBuildingRef->GetTransform().GetLocation();
			FVector SpawnLoc = FVector((Loc1.X + Loc2.X) / 2, (Loc1.Y + Loc2.Y) / 2, 100);
			double Cos = Loc1.X>Loc2.X ? FVector::LeftVector.CosineAngle2D(Loc1 - Loc2) : FVector::LeftVector.CosineAngle2D(Loc2 - Loc1);
			UE_LOG(LogTemp,Warning,TEXT("%s"),*(Loc1-Loc2).ToString())
			double XScaleLength = FMath::Sqrt(FMath::Pow(Loc2.X - Loc1.X, 2) + FMath::Pow(Loc2.Y - Loc1.Y, 2));
			double DegreesBetweenVectors = FMath::Acos(Cos) * (180 / 3.14)+90;
			FRotator SpawnRot = FRotator(0, DegreesBetweenVectors, 0);
			if (AStaticMeshActor* NewMesh = GetWorld()->SpawnActor<AStaticMeshActor>(GameMode->LineMesh, SpawnLoc, SpawnRot))
			{
				if (GameMode->LineMesh)
				{
					
					NewMesh->SetActorScale3D(FVector((XScaleLength)/100,0.2, 1));
					UE_LOG(LogTemp, Warning, TEXT("FINAL?"))
				}
				
			}
			GameMode->IsConnecting = false;
		}
		else
		{
			if (!IsConnected||!IsInteractable) return;
			UE_LOG(LogTemp, Warning, TEXT("connecting false"));
			GameMode->FirstBuildingRef = this;
			GameMode->IsConnecting = true;
		}
	}
}

