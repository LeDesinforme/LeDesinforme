#include "Employee/BTT_Work.h"


UBTT_Work::UBTT_Work(FObjectInitializer const& _objectInitializer)
{
	NodeName = TEXT("Work");
}

EBTNodeResult::Type UBTT_Work::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	return Super::ExecuteTask(_ownerComp, _nodeMemory);
}
