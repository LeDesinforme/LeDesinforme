#include "Employee/Employee.h"

#include "Algo/RandomShuffle.h"
#include "Game/GameManager.h"
#include "GameFramework/CharacterMovementComponent.h"


const int WALK_SPEED = 300.f;


AEmployee::AEmployee()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
}

void AEmployee::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(m_timerHandle, this, &AEmployee::AddToGameManagerCallback, FMath::RandRange(0.3f, 1.0f), false);
}

void AEmployee::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void AEmployee::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);
}

void AEmployee::AddToGameManagerCallback()
{
	// Create Employee and assign his computer
	if (!AGameManager::availableComputers.IsEmpty())
	{
		// Get random computer in array
		int randomIndex = FMath::RandRange(0, AGameManager::availableComputers.Num() - 1);
		AComputer* assignedComputer = AGameManager::availableComputers[randomIndex];
		// Remove computer from available computers
		AGameManager::availableComputers.RemoveAt(randomIndex);
		// Assign this Employee and Computer in the TMap of GameManager
		AGameManager::deskMap.Add(this, assignedComputer);
		AGameManager::SetupEmployee(this);
	}
}

ABreakPointPath* AEmployee::GetBreakPointPath() const
{
	return m_breakPointPath;
}

UBehaviorTree* AEmployee::GetBehaviorTree() const
{
	return m_behaviorTree;
}

EEmployeeType AEmployee::GetEmployeeType() const
{
	return m_employeeType;
}

void AEmployee::SetEmployeeType(EEmployeeType _employeeType)
{
	m_employeeType = _employeeType;
}

bool AEmployee::BeReported()
{
	if (m_employeeType != EEmployeeType::GOOD)
		return true;
	else
		return false;
}
