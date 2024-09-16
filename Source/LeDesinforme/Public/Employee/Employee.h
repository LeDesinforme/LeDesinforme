#pragma once

#include "CoreMinimal.h"
#include "BreakPointPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Employee.generated.h"


UENUM(BlueprintType)
enum EEmployeeType
{
	GOOD		UMETA(DisplayName = "Good"),
	FAKE_NEWS	UMETA(DisplayName = "Fake_News"),
	AI			UMETA(DisplayName = "Ai"),
	OI			UMETA(DisplayName = "Oi")
};


UCLASS()
class LEDESINFORME_API AEmployee : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EEmployeeType> m_employeeType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_behaviorTree = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	ABreakPointPath* m_breakPointPath = nullptr;

	FTimerHandle m_timerHandle;
	
public:
	AEmployee();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float _deltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* _playerInputComponent) override;
	void AddToGameManagerCallback();
	
	ABreakPointPath* GetBreakPointPath() const;
	UBehaviorTree* GetBehaviorTree() const;
	EEmployeeType GetEmployeeType() const;

	void SetEmployeeType(EEmployeeType _employeeType);

	UFUNCTION(BlueprintCallable, Category = "Employee")
	bool BeReported();
};
