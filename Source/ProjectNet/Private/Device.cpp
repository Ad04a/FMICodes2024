// Fill out your copyright notice in the Description page of Project Settings.


#include "Device.h"
#include "Cable.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
ADevice::ADevice()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADevice::BeginPlay()
{
	Super::BeginPlay();

	TArray< AActor* > tempChildActors;
	UWorld* World= GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ADevice::BeginPlay()  World == nullptr"));
		return;
	}
	UGameplayStatics::GetAllActorsOfClass(World, ADevice::StaticClass(), tempChildActors);

	uint32 count = tempChildActors.Num();
	UE_LOG(LogTemp, Error, TEXT("%d"), count);
	for (int i = 0; i < tempChildActors.Num(); i++) 
	{
		UE_LOG(LogTemp, Error, TEXT("i = %d"), i);
		ADevice* Child = Cast<ADevice>(tempChildActors[i]);
		if (Child == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ADevice::BeginPlay()  Child == nullptr"));
			break;
		}
		TArray< UBoxComponent* > tempChildActors2;
		Child->GetComponents<UBoxComponent*>(tempChildActors2);
		if (tempChildActors2.Num() <= 0)
		{ 
			UE_LOG(LogTemp, Warning, TEXT("Grandchildren are empty")); 
			break; 
		}
		else 
		{
			for (int j = 0; j < tempChildActors2.Num(); j++)
			{
				tempChildActors2[j]->OnComponentBeginOverlap.AddDynamic(this, &ADevice::AttachCable);
			}
		}
		
		//UE_LOG(LogTemp, Warning, TEXT("ADevice::BeginPlay()  Child != nullptr"));
	}
}

// Called every frame
void ADevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADevice::AttachCable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACable* AttachedCable = Cast<ACable>(OtherActor);
	if (AttachedCable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice::AttachCable::AttachedCable == nullptr"));
		return;
	}
	UBoxComponent* BoxComp = Cast<UBoxComponent>(OverlappedComponent);
	if (BoxComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADevice::AttachCable::BoxComp == nullptr"));
		return;
	}
	/*FPort* AttachedPort = nullptr;
	for (int i = 0; i < Ports.Num(); i++)
	{
		if (Ports[i].HitBox == Socket)
		{
			AttachedPort = &Ports[i];
			break;
		}
	}
	if (AttachedCable->Type == AttachedPort->Hole)*/
	if(BoxComp->ComponentHasTag(AttachedCable->Mesh->ComponentTags[0]) && AttachedCable->bIsHeld)
	{
		AttachedCable->SetIsHeld(false);
		BoxComp->SetGenerateOverlapEvents(false);
		AttachedCable->AttachToComponent(OverlappedComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Socket"));
		//AttachedCable->SetActorLocation(FVector(0,0, 10));
		
		UGameplayStatics::SpawnSound2D(GetWorld(), AttachedCableSound);
		AttachedCableEvent.Broadcast();
			
	}
	
	
	
}



