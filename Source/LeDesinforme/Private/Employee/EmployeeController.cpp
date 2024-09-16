#include "Employee/EmployeeController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/PlayerCharacter.h"


AEmployeeController::AEmployeeController(FObjectInitializer const& _objectInitializer)
{
	SetupPerceptionSystem();
}

void AEmployeeController::SetBlackBoard(UBlackboardComponent* _blackBoard)
{
	Blackboard = _blackBoard;
}

void AEmployeeController::SetupPerceptionSystem()
{
	m_sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (m_sightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));
		m_sightConfig->SightRadius = 200.f;
		m_sightConfig->LoseSightRadius = m_sightConfig->SightRadius + 25.f;
		m_sightConfig->PeripheralVisionAngleDegrees = 60.f;
		m_sightConfig->SetMaxAge(5.f);
		m_sightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		m_sightConfig->DetectionByAffiliation.bDetectEnemies = true;
		m_sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		m_sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*m_sightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEmployeeController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*m_sightConfig);
	}
}

void AEmployeeController::OnTargetDetected(AActor* _actor, FAIStimulus const _stimulus)
{
	if (auto* const player = Cast<APlayerCharacter>(_actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", _stimulus.WasSuccessfullySensed());
		GetBlackboardComponent()->SetValueAsObject("Player", player);
	}
}

void AEmployeeController::OnPossess(APawn* _inPawn)
{
	Super::OnPossess(_inPawn);
}