// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OverWorldGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNET_API AOverWorldGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AOverWorldGameModeBase();
	UPROPERTY()
	int IsConnecting;

	UPROPERTY()
	class ABuilding* FirstBuildingRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class AStaticMeshActor> LineMesh;
};
