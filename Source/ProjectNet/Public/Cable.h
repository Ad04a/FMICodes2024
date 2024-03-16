// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableTypes.h"
#include "Cable.generated.h"


UCLASS()
class PROJECTNET_API ACable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACable();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	bool bIsHeld = false;

	UPROPERTY(EditAnywhere)
	ECableTypes Type = ECableTypes::LAN;

protected:
	UPROPERTY(EditAnywhere)
	APlayerController* PlayerController;
	
	UPROPERTY(EditAnywhere)
	float LastMousePositionX;

	UPROPERTY(EditAnywhere)
	float LastMousePositionZ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PickedUp(AActor* Actor, FKey Key);


	void SetIsHeld(bool IsHeld) { bIsHeld = IsHeld; }

};
