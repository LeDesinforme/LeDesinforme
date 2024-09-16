#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Work.generated.h"


UCLASS()
class LEDESINFORME_API UBTT_Work : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTT_Work(FObjectInitializer const& _objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
