#include "Employee/BTT_FindBreakPoint.h"

#include "Employee/BreakPointPath.h"
#include "Employee/Employee.h"
#include "Employee/EmployeeController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTT_FindBreakPoint::UBTT_FindBreakPoint(FObjectInitializer const& _objectInitializer)
{
	NodeName = TEXT("FindBreakPoint");
}

EBTNodeResult::Type UBTT_FindBreakPoint::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Get EmployeeController
	if (auto* const employeeController = Cast<AEmployeeController>(_ownerComp.GetAIOwner()))
	{
		// Get the BlackBoard component from the behavior tree
		if (auto* const blackBoardComponent = _ownerComp.GetBlackboardComponent())
		{
			// Get Employee
			if (auto* employee = Cast<AEmployee>(employeeController->GetPawn()))
			{
				// Select a random vector in the breakPointPath
				int selectedPathId = FMath::RandRange(0, employee->GetBreakPointPath()->Num() - 1);
				// Get the local selected path vector
				FVector pathPoint = employee->GetBreakPointPath()->GetBreakPoints()[selectedPathId];
				// Convert the local pathPoint vector to a global vector
				auto const globalPathPoint = employee->GetBreakPointPath()->GetActorTransform().TransformPosition(pathPoint);
				// Set the blackboard key
				blackBoardComponent->SetValueAsVector(m_selectedBreakPoint.SelectedKeyName, globalPathPoint);

				FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
