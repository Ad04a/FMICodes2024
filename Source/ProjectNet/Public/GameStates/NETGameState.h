// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NETGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNET_API ANETGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool IsCentralSpawned = false;
	UPROPERTY()
	int SpawnedBuildingsCount = 0;

	virtual void HandleBeginPlay() override;
};
