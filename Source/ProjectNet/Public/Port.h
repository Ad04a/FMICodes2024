#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableTypes.h"
#include "Port.generated.h"


USTRUCT(BlueprintType)
struct FPort
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECableTypes Hole = ECableTypes::LAN;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* HitBox;
};