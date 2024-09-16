#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/Computer.h"
#include "Employee/Employee.h"
#include "GameManager.generated.h"


UCLASS()
class LEDESINFORME_API AGameManager : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle m_timerHandle;
	
public:
	static TArray<AComputer*> availableComputers;
	static TMap<AEmployee*, AComputer*> deskMap;

public:	
	AGameManager() = default;
	~AGameManager();

private:
	void SetupBadEmployeeCallback();
	AEmployee* SelectBadEmployee();
	// Select random bad employee type and set it to the employee
	void SetBadEmployeeType(AEmployee* _badEmployee);
	
public:
	virtual void BeginPlay() override;
	static void SetupEmployee(AEmployee* _employee);
	static void SetupComputer(AComputer* _computer);
	
	static AComputer* GetAssignedComputer(const AEmployee* _employee);
	static AEmployee* GetAssignedEmployee(const AComputer* _computer);

	UFUNCTION(BlueprintCallable)
	static void GameOver();
	UFUNCTION(BlueprintCallable)
	static void GameWin();
};
