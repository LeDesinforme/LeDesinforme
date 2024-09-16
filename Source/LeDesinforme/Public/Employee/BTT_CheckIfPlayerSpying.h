#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_CheckIfPlayerSpying.generated.h"


UCLASS()
class LEDESINFORME_API UBTT_CheckIfPlayerSpying : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	// UPROPERTY(EditAnywhere, Category = "BlackBoard", meta = (AllowPrivateAccess = "true"))
	// FBlackboardKeySelector m_player;

public:
	explicit UBTT_CheckIfPlayerSpying(FObjectInitializer const& _objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
