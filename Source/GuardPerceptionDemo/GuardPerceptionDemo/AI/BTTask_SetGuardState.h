#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GuardState.h"
#include "BTTask_SetGuardState.generated.h"

UCLASS()
class GUARDPERCEPTIONDEMO_API UBTTask_SetGuardState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetGuardState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "AI|State")
	EGuardState NewState = EGuardState::Patrol;
};