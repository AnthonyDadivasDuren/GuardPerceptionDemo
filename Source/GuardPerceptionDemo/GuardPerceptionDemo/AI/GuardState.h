
#pragma once

#include "CoreMinimal.h"
#include "GuardState.generated.h"

UENUM(BlueprintType)
enum class EGuardState : uint8
{
	Patrol UMETA(DisplayName = "Patrol"),
	Chase  UMETA(DisplayName = "Chase"),
	Investigate UMETA(DisplayName = "Investigate"),
};
