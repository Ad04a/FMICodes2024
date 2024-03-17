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
	int RouterCount = OptionsString[0] - '0';
	for(int i=0;i<RouterCount;i++)
	{
		ADevice* Device = World->SpawnActor<ADevice>(RouterClass, SpawnLocations[SpawnedDevices], FRotator(0, 0, 0));
		Device->AttachedCableEvent.AddDynamic(this, &AMiniGameModeBase::ConnectCable);
		SpawnedDevices++;
		int NewCables = FMath::RandRange(1, 2);
		CablesNeededForConnection += NewCables;
		for(int j = 0; j<NewCables; j++)
		{
			int CableType = 0;
			World->SpawnActor<ACable>(CableClasses[CableType], SpawnLocations[SpawnedCables+3], FRotator(0, 0, 0));
			SpawnedCables++;
		}
	}
	int DecoderCount = OptionsString[1] - '0';
	for (int i = 0; i < DecoderCount; i++)
	{
		ADevice* Device = World->SpawnActor<ADevice>(DecoderClass, SpawnLocations[SpawnedDevices], FRotator(0,0,0));
		Device->AttachedCableEvent.AddDynamic(this, &AMiniGameModeBase::ConnectCable);
		SpawnedDevices++;
		int NewCables = FMath::RandRange(1, 2);
		CablesNeededForConnection += NewCables;
		for (int j = 0; j < NewCables; j++)
		{
			int CableType = FMath::RandRange(0, 1);
			World->SpawnActor<ACable>(CableClasses[CableType], SpawnLocations[SpawnedCables+3], FRotator(0, 0, 0));
			SpawnedCables++;
		}
	}
	int SwitchCount = OptionsString[2] - '0';
	for (int i = 0; i < SwitchCount; i++)
	{
		ADevice* Device = World->SpawnActor<ADevice>(SwitchClass, SpawnLocations[SpawnedDevices], FRotator(0, 0, 0));
		Device->AttachedCableEvent.AddDynamic(this, &AMiniGameModeBase::ConnectCable);
		SpawnedDevices++;
		int NewCables = FMath::RandRange(2, 3);
		CablesNeededForConnection += NewCables;
		for (int j = 0; j < NewCables; j++)
		{
			int CableType = FMath::RandRange(2, 3);
			World->SpawnActor<ACable>(CableClasses[CableType], SpawnLocations[SpawnedCables+3], FRotator(0, 0, 0));
			SpawnedCables++;
		}
	}
	
}

void AMiniGameModeBase::ConnectCable()
{
	CablesConnected++;
}
