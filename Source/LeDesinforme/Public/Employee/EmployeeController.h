#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EmployeeController.generated.h"


UCLASS()
class LEDESINFORME_API AEmployeeController : public AAIController
{
	GENERATED_BODY()

private:
	class UAISenseConfig_Sight* m_sightConfig;

public:
	explicit AEmployeeController(FObjectInitializer const& _objectInitializer);
	
private:
	void SetupPerceptionSystem();
	UFUNCTION()
	void OnTargetDetected(AActor* _actor, FAIStimulus const _stimulus);

protected:
	virtual void OnPossess(APawn* _inPawn) override;

public:
	void SetBlackBoard(UBlackboardComponent* _blackBoard);
};
