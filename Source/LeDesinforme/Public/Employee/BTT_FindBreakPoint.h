#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindBreakPoint.generated.h"


UCLASS()
class LEDESINFORME_API UBTT_FindBreakPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "BlackBoard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector m_selectedBreakPoint;

public:
	explicit UBTT_FindBreakPoint(FObjectInitializer const& _objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
