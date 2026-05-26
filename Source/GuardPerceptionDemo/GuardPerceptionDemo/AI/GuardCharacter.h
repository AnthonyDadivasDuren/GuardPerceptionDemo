#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GuardState.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Patrol")
	EGuardState CurrentState = EGuardState::Patrol;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "AI|State")
	void OnGuardStateChanged(EGuardState NewState);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement")
	float PatrolSpeed = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement")
	float InvestigateSpeed = 280.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement")
	float ChaseSpeed = 450.0f;
};
