#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindDeskLocationActor.generated.h"


UCLASS()
class LEDESINFORME_API UBTT_FindDeskLocationActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "BlackBoard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector m_selectedDeskLocationActor;

public:
	explicit UBTT_FindDeskLocationActor(FObjectInitializer const& _objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
