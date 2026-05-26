#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GuardCharacter.generated.h"

UCLASS()
class GUARDPERCEPTIONDEMO_API AGuardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGuardCharacter();

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AI|Patrol")
	TArray<AActor*> PatrolPoints;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AI|Patrol")
	int32 CurrentPatrolIndex = 0;
};
