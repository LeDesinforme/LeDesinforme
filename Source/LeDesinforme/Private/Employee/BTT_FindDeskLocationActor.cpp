#include "Employee/BTT_FindDeskLocationActor.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Employee/Employee.h"
#include "Employee/EmployeeController.h"
#include "Game/GameManager.h"


UBTT_FindDeskLocationActor::UBTT_FindDeskLocationActor(FObjectInitializer const& _objectInitializer)
{
	NodeName = TEXT("FindDeskLocationActor");
}

EBTNodeResult::Type UBTT_FindDeskLocationActor::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Get EmployeeController
	if (auto* const employeeController = Cast<AEmployeeController>(_ownerComp.GetAIOwner()))
	{
		// Get BlackBoard component
		if (auto* const blackBoardComponent = _ownerComp.GetBlackboardComponent())
		{
			// Get Employee
			if (auto* employee = Cast<AEmployee>(employeeController->GetPawn()))
			{
				FVector deskLocationActor = AGameManager::deskMap[employee]->GetDeskLocationActor()->GetActorLocation();
				blackBoardComponent->SetValueAsVector(m_selectedDeskLocationActor.SelectedKeyName, deskLocationActor);

				FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
