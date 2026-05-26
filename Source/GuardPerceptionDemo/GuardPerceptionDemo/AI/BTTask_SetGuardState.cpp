#include "GuardPerceptionDemo/AI/BTTask_SetGuardState.h"

#include "AIController.h"
#include "GuardCharacter.h"

UBTTask_SetGuardState::UBTTask_SetGuardState()
{
	NodeName = "Set Guard State";
}

EBTNodeResult::Type UBTTask_SetGuardState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AGuardCharacter* GuardCharacter = Cast<AGuardCharacter>(AIController->GetPawn());
	if (!GuardCharacter)
	{
		return EBTNodeResult::Failed;
	}

	if (GuardCharacter->CurrentState != NewState)
	{
		GuardCharacter->CurrentState = NewState;
		GuardCharacter->OnGuardStateChanged(NewState);
	}

	return EBTNodeResult::Succeeded;
}