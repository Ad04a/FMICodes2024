// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Port.h"
#include "Device.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCableAttachedSignature);

UCLASS()
class PROJECTNET_API ADevice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevice();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<FPort> Ports;

	UPROPERTY(EditAnywhere)
	FCableAttachedSignature AttachedCableEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AttachCable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
