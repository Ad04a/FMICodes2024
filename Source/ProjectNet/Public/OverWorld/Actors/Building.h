// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class PROJECTNET_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Materials")
	TArray<UMaterial*> PossibleMaterials;

	UFUNCTION(BlueprintCallable)
	void DrawLine();

	UPROPERTY(BlueprintReadOnly)
	int SwitchCount;

	UPROPERTY(BlueprintReadOnly)
	int RouterCount;

	UPROPERTY(BlueprintReadOnly)
	int DecoderCount;

	UPROPERTY(BlueprintReadOnly)
	bool IsInteractable;

	UPROPERTY()
	bool IsConnected;

	UPROPERTY()
	bool IsCentral;
};
