#include "Employee/BTT_SetKeyValueBB.h"

#include "Employee/EmployeeController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTT_SetKeyValueBB::UBTT_SetKeyValueBB(FObjectInitializer const& _objectInitializer)
{
	NodeName = TEXT("SetKeyValueBB");
}


EBTNodeResult::Type UBTT_SetKeyValueBB::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Get EmployeeController
	if (auto* const employeeController = Cast<AEmployeeController>(_ownerComp.GetAIOwner()))
	{
		// Get the BlackBoard component from the behavior tree
		if (auto* blackBoardComponent = _ownerComp.GetBlackboardComponent())
		{
			blackBoardComponent->SetValueAsBool(m_key.SelectedKeyName, m_value);

			FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}