#pragma once

#include "CoreMinimal.h"
#include "UIDelegates.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonWithStringClicked, FString, String);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClicked);