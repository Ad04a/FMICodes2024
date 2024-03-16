#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CableTypes.generated.h"


UENUM(BlueprintType)
enum class ECableTypes : uint8
{
	HDMI = 0,
	LAN = 1,
	TP = 2,
	FiberOptic = 3,
	Coaxical = 4
};