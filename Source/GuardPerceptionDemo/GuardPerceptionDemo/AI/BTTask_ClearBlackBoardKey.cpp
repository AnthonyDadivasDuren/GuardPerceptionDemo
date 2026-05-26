#include "GuardPerceptionDemo/AI/BTTask_ClearBlackBoardKey.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackBoardKey::UBTTask_ClearBlackBoardKey()
{
	NodeName = "Clear Black Board Key";
}

EBTNodeResult::Type UBTTask_ClearBlackBoardKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackboardComponent->ClearValue(KeyToClear.SelectedKeyName);
	
	return EBTNodeResult::Succeeded;
}

