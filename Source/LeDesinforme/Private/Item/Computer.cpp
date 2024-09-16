// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Computer.h"

#include "Game/GameManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Employee/EmployeeController.h"
#include "Employee/Employee.h"

AComputer::AComputer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AComputer::BeginPlay()
{
	Super::BeginPlay();

	if (!m_isPlayerComputer)
	{
		GetWorld()->GetTimerManager().SetTimer(m_timerHandle, this, &AComputer::AddToGameManagerCallback, 0.2f, false);
	}
}

void AComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AComputer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AComputer::AddToGameManagerCallback()
{
	AGameManager::SetupComputer(this);
}

ADeskLocationActor* AComputer::GetDeskLocationActor()
{
	return m_deskLocationActor;
}

bool AComputer::GetEmpolyeeIsAtDesk()
{
	TObjectPtr<AEmployee> employee = AGameManager::GetAssignedEmployee(this);
	if (employee)
	{
		TObjectPtr<AEmployeeController> employeeController = Cast<AEmployeeController>(employee->GetController());

		return employeeController->GetBlackboardComponent()->GetValueAsBool("IsAtDesk");
	}
	else
		return false;

}

EEmployeeType AComputer::GetEmployeeType()
{
	TObjectPtr<AEmployee> employee = AGameManager::GetAssignedEmployee(this);

	return employee->GetEmployeeType();
}

FString AComputer::ReadNewsTitle()
{
	return news.title;
}

FString AComputer::ReadNewsContents()
{
	return news.contents;
}

bool AComputer::CheckNewsTruth()
{
	return news.bIsTrue;
}

FString AComputer::GetNewsSubject()
{
	return news.subject;
}

ENewsType AComputer::GetNewsType()
{
	return news.newsType;
}

void AComputer::SetNewsType(ENewsType type)
{
	news = UReadWriteTxtHelper::RandomRead("Car", type);
}