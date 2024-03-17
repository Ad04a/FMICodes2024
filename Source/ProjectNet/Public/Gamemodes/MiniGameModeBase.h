// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Device.h"
#include "Cable.h"
#include "Kismet/GameplayStatics.h"
#include "MiniGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNET_API AMiniGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADevice> RouterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADevice> DecoderClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADevice> SwitchClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADevice> TVClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ACable>> CableClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CablesNeededForConnection = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CablesConnected = 0;

private:
	int SpawnedCables = 0;

	int SpawnedDevices = 0;

public:
	void StartPlay();

	UFUNCTION()
	void ConnectCable();

	UFUNCTION()
	void CompleteGameMode();
};
