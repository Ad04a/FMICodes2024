// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/MiniGameModeBase.h"

void AMiniGameModeBase::StartPlay()
{
	Super::StartPlay();
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AMiniGameModeBase::StartPlay()  World == nullptr"));
		return;
	}
	if (OptionsString.IsEmpty()) 
	{
		OptionsString = FString("110");
	}
	
	//mute other player
	
	
	int RouterCount = OptionsString[1] - '0';
	UE_LOG(LogTemp, Error, TEXT("AMiniGameModeBase::StartPlay()  RouterCount = %d"), RouterCount);
	for(int i=0;i<RouterCount;i++)
	{
		ADevice* Device = World->SpawnActor<ADevice>(RouterClass, SpawnLocations[i], FRotator(0, 0, 0));
		Device->AttachedCableEvent.AddDynamic(this, &AMiniGameModeBase::ConnectCable);
		SpawnedDevices++;
		int NewCables = FMath::RandRange(1, 2);
		CablesNeededForConnection += NewCables;
		for(int j = 0; j<NewCables; j++)
		{
			int CableType = 1;
			World->SpawnActor<ACable>(CableClasses[CableType], SpawnLocations[SpawnedCables+12], FRotator(0, 0, 0));
			SpawnedCables++;
		}
	}
	int DecoderCount = OptionsString[2] - '0';
	UE_LOG(LogTemp, Error, TEXT("AMiniGameModeBase::StartPlay()  Switch = %d"), DecoderCount);
	for (int i = 0; i < DecoderCount; i++)
	{
		ADevice* Device = World->SpawnActor<ADevice>(SwitchClass, SpawnLocations[3+i], FRotator(0,0,0));
		Device->AttachedCableEvent.AddDynamic(this, &AMiniGameModeBase::ConnectCable);
		SpawnedDevices++;
		int NewCables = FMath::RandRange(1, 2);
		CablesNeededForConnection += NewCables;
		for (int j = 0; j < NewCables; j++)
		{
			int CableType = FMath::RandRange(2, 3);
			World->SpawnActor<ACable>(CableClasses[CableType], SpawnLocations[SpawnedCables+12], FRotator(0, 0, 0));
			SpawnedCables++;
		}
	}
	int SwitchCount = OptionsString[3] - '0';
	UE_LOG(LogTemp, Error, TEXT("AMiniGameModeBase::StartPlay()  decoder = %d"), SwitchCount);
	for (int i = 0; i < SwitchCount; i++)
	{
		ADevice* Device = World->SpawnActor<ADevice>(DecoderClass, SpawnLocations[6+i], FRotator(0, 0, 0));
		ADevice* Device2 = World->SpawnActor<ADevice>(TVClass, SpawnLocations[9 + i], FRotator(0, 0, 0));
		Device->AttachedCableEvent.AddDynamic(this, &AMiniGameModeBase::ConnectCable);
		Device2->AttachedCableEvent.AddDynamic(this, &AMiniGameModeBase::ConnectCable);
		SpawnedDevices++;
		SpawnedDevices++;
		
		int NewCables = FMath::RandRange(1, 2);
		CablesNeededForConnection += NewCables;
		for (int j = 0; j < NewCables; j++)
		{
			int CableType = FMath::RandRange(0, 1);
			World->SpawnActor<ACable>(CableClasses[CableType], SpawnLocations[SpawnedCables+12], FRotator(0, 0, 0));
			SpawnedCables++;
		}
	}
	
}

void AMiniGameModeBase::ConnectCable()
{
	CablesConnected++;
	if (CablesConnected >= CablesNeededForConnection)
	{
		CompleteGameMode();
	}
}

void AMiniGameModeBase::CompleteGameMode()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AMiniGameModeBase::StartPlay()  World == nullptr"));
		return;
	}
	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	PC->GameplayUnmuteAllPlayers();
	UE_LOG(LogTemp, Error, TEXT("all cables attached!"));
}
