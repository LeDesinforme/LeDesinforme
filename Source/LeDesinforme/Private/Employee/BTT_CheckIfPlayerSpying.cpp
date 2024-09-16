#include "Employee/BTT_CheckIfPlayerSpying.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Employee/Employee.h"
#include "Employee/EmployeeController.h"
#include "Game/GameManager.h"
#include "Player/PlayerCharacter.h"


UBTT_CheckIfPlayerSpying::UBTT_CheckIfPlayerSpying(FObjectInitializer const& _objectInitializer)
{
	NodeName = TEXT("CheckIfPlayerSpying");
}

EBTNodeResult::Type UBTT_CheckIfPlayerSpying::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
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
				// Get player
				UObject* playerObject = blackBoardComponent->GetValueAsObject("Player");
				APlayerCharacter* player = Cast<APlayerCharacter>(playerObject);

				// Get assigned computer
				AComputer* computer = AGameManager::GetAssignedComputer(employee);
				// Check if player is focused on assigned computer

				if (player->CameraState == ECameraState::LookScreen)
				{
					UE_LOG(LogTemp, Warning, TEXT("YOU GOT CAUGHT"));
					AGameManager::GameOver();
				}
			}
		}
	}

	FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
