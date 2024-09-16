#include "Game/GameManager.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Employee/EmployeeController.h"


const float TIME_BEFORE_INIT_BAD_EMPLOYEE = 1.5f; 

TArray<AComputer*> AGameManager::availableComputers;
TMap<AEmployee*, AComputer*> AGameManager::deskMap;


AGameManager::~AGameManager()
{
	availableComputers.Empty();
	deskMap.Empty();
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
 
	GetWorld()->GetTimerManager().SetTimer(m_timerHandle, this, &AGameManager::SetupBadEmployeeCallback, TIME_BEFORE_INIT_BAD_EMPLOYEE, false);
}

void AGameManager::SetupEmployee(AEmployee* _employee)
{
	AEmployeeController* _employeeController = Cast<AEmployeeController>(_employee->GetController());

	// Setup BT
	_employee->SetEmployeeType(EEmployeeType::GOOD);
	GetAssignedComputer(_employee)->SetNewsType(ENewsType::TrueNews);
	if (UBehaviorTree* const behaviorTree = _employee->GetBehaviorTree())
	{
		UBlackboardComponent* blackBoard;
		_employeeController->UseBlackboard(behaviorTree->BlackboardAsset, blackBoard);
		_employeeController->SetBlackBoard(blackBoard);
		_employeeController->RunBehaviorTree(behaviorTree);
	}

	// Setup BB keys
	_employeeController->GetBlackboardComponent()->SetValueAsBool("WantCoffeeBreak", false);
	_employeeController->GetBlackboardComponent()->SetValueAsBool("IsAtDesk", false);
	AComputer* computer = deskMap[_employee];
	if (computer)
	{
		_employeeController->GetBlackboardComponent()->SetValueAsVector("DeskLocation", computer->GetDeskLocationActor()->GetActorLocation());
	}
}

void AGameManager::SetupComputer(AComputer* _computer)
{
	availableComputers.Push(_computer);
}

void AGameManager::SetupBadEmployeeCallback()
{
	AEmployee* badEmployee = SelectBadEmployee();
	SetBadEmployeeType(badEmployee);
}

AEmployee* AGameManager::SelectBadEmployee()
{
	// Get a random employee
	int badEmployeeId = FMath::RandRange(0, deskMap.Num() - 1);
	// Convert deskMap to an array
	TArray<TTuple<AEmployee*, AComputer*>> deskArray = deskMap.Array();
	for (int i = 0; i < deskArray.Num(); i++)
	{
		if (i == badEmployeeId)
		{
			AEmployee* badEmployee = Cast<AEmployee>(deskArray[i].Key);
			return  badEmployee;
		}
	}

	return nullptr;
}

void AGameManager::SetBadEmployeeType(AEmployee* _badEmployee)
{
	int type = FMath::RandRange(0, 2);

	//AEmployeeController* badEmployeeController = Cast<AEmployeeController>(_badEmployee->GetController());
	//badEmployeeController->GetBlackboardComponent()->GetValueAsBool("IsAtDesk");

	switch (type)
	{
	case 0:
		_badEmployee->SetEmployeeType(EEmployeeType::FAKE_NEWS);
		GetAssignedComputer(_badEmployee)->SetNewsType(ENewsType::FakeNews);
		break;

	case 1:
		_badEmployee->SetEmployeeType(EEmployeeType::AI);
		GetAssignedComputer(_badEmployee)->SetNewsType(ENewsType::AINews);
		break;

	case 2:
		_badEmployee->SetEmployeeType(EEmployeeType::OI);
		GetAssignedComputer(_badEmployee)->SetNewsType(ENewsType::OINews);
		break;

	default:
		break;
	}
}

AComputer* AGameManager::GetAssignedComputer(const AEmployee* _employee)
{
	return deskMap.FindRef(_employee);
}

AEmployee* AGameManager::GetAssignedEmployee(const AComputer* _computer)
{
	for (const TPair<AEmployee*, AComputer*>& pair : deskMap)
	{
		if (pair.Value == _computer)
		{
			return pair.Key;
		}
	}

	return nullptr;
}

void AGameManager::GameOver()
{
	
}

void AGameManager::GameWin()
{

}
