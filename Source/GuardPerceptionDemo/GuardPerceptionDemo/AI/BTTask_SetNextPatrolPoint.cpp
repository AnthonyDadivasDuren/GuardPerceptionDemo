#include "BTTask_SetNextPatrolPoint.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GuardCharacter.h"

UBTTask_SetNextPatrolPoint::UBTTask_SetNextPatrolPoint()
{
	NodeName = "Set Next Patrol Point";
}

EBTNodeResult::Type UBTTask_SetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetNextPatrolPoint failed: No AIController"));
		return EBTNodeResult::Failed;
	}
	
	AGuardCharacter* GuardCharacter = Cast<AGuardCharacter>(AIController->GetPawn());
	if (!GuardCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetNextPatrolPoint failed: Pawn is not AGuardCharacter"));
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (!BlackboardComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("SetNextPatrolPoint failed: No BlackboardComponent"));
			return EBTNodeResult::Failed;
		}
	
	if (GuardCharacter->PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetNextPatrolPoint failed: PatrolPoints array is empty"));
		return EBTNodeResult::Failed;
	}
	
	if (!GuardCharacter->PatrolPoints.IsValidIndex(GuardCharacter->CurrentPatrolIndex))
	{
		GuardCharacter->CurrentPatrolIndex = 0;
	}

	AActor* PatrolPoint = GuardCharacter->PatrolPoints[GuardCharacter->CurrentPatrolIndex];
	if (!PatrolPoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetNextPatrolPoint failed: PatrolPoint is null"));
		return EBTNodeResult::Failed;
	}
	
	const FVector PatrolLocation = PatrolPoint->GetActorLocation();

	BlackboardComponent->SetValueAsVector(PatrolLocationKeyName, PatrolLocation);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("SetNextPatrolPoint succeeded: %s at %s"),
		*PatrolPoint->GetName(),
		*PatrolLocation.ToString()
	);
	
	GuardCharacter->CurrentPatrolIndex++;
	
	if (GuardCharacter->CurrentPatrolIndex >= GuardCharacter->PatrolPoints.Num())
	{
		GuardCharacter->CurrentPatrolIndex = 0;
	}
	
	return EBTNodeResult::Succeeded;
}
