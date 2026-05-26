
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_ClearBlackBoardKey.generated.h"

UCLASS()
class GUARDPERCEPTIONDEMO_API UBTTask_ClearBlackBoardKey : public UBTTaskNode
{
	GENERATED_BODY()
	
	
public:
	UBTTask_ClearBlackBoardKey();
	
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "BlackBoard")
	FBlackboardKeySelector KeyToClear;
};
