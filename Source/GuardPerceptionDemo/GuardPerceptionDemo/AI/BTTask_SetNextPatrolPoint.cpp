#include "BTTask_SetNextPatrolPoint.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"

UBTTask_SetNextPatrolPoint::UBTTask_SetNextPatrolPoint()
{
	NodeName = "Set Next Patrol Point";
}

EBTNodeResult::Type UBTTask_SetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (!BlackboardComponent)
		{
			return EBTNodeResult::Failed;
		}
		
		
		const FVector Origin = ControlledPawn->GetActorLocation();
		const float PatrolRadius = 800.0f;
		
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(ControlledPawn->GetWorld());
		
		if (!NavSystem)
		{
			return EBTNodeResult::Failed;
		}
		
		FNavLocation RandomLocation;
		const bool bFoundLocation = NavSystem->GetRandomReachablePointInRadius(
			Origin,
			PatrolRadius,
			RandomLocation
		);
		
	if (!bFoundLocation)
	{
		return EBTNodeResult::Failed;
	}
		
	BlackboardComponent->SetValueAsVector(PatrolLocationKeyName, RandomLocation.Location);
		
	return EBTNodeResult::Succeeded;
	
}
