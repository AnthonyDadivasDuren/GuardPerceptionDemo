#include "BTTask_SetGuardState.h"

#include "AIController.h"
#include "GuardCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	float NewSpeed = GuardCharacter->PatrolSpeed;

	switch (NewState)
	{
	case EGuardState::Patrol:
		NewSpeed = GuardCharacter->PatrolSpeed;
		break;

	case EGuardState::Chase:
		NewSpeed = GuardCharacter->ChaseSpeed;
		break;

	case EGuardState::Investigate:
		NewSpeed = GuardCharacter->InvestigateSpeed;
		break;

	default:
		break;
	}

	if (UCharacterMovementComponent* MovementComponent = GuardCharacter->GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = NewSpeed;
	}

	if (GuardCharacter->CurrentState != NewState)
	{
		GuardCharacter->CurrentState = NewState;
		GuardCharacter->OnGuardStateChanged(NewState);
	}

	return EBTNodeResult::Succeeded;
}