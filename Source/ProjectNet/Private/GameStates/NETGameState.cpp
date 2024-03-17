// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/NETGameState.h"

void ANETGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();
	IsCentralSpawned = false;
	SpawnedBuildingsCount = 0;
}
