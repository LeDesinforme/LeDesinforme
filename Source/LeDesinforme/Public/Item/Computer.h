// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeskLocationActor.h"
#include "Item/Item.h"
#include "Tools/ReadWriteTxtHelper.h"
#include "Employee/Employee.h"
#include "Computer.generated.h"

/**
 * 
 */
UCLASS()
class LEDESINFORME_API AComputer : public AItem
{
	GENERATED_BODY()

private:
	FTimerHandle m_timerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Employee", meta = (AllowPrivateAccess = "true"))
	ADeskLocationActor* m_deskLocationActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	bool m_isPlayerComputer = false;
	
public:
	AComputer();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CallMessageBox();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowMessageBox();

	UFUNCTION(BlueprintImplementableEvent)
	void HideMessageBox();

	UFUNCTION(BlueprintImplementableEvent)
	void DeleteMessageBox();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddToGameManagerCallback();
	ADeskLocationActor* GetDeskLocationActor();

	UFUNCTION(BlueprintCallable, Category = "Employee")
	bool GetEmpolyeeIsAtDesk();

	UFUNCTION(BlueprintCallable, Category = "Empolyee")
	EEmployeeType GetEmployeeType();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")	
	FNews news;

	UFUNCTION(BlueprintCallable, Category = "News")
	FString ReadNewsTitle();

	UFUNCTION(BlueprintCallable, Category = "News")
	FString ReadNewsContents();

	UFUNCTION(BlueprintCallable, Category = "News")
	bool CheckNewsTruth();

	UFUNCTION(BlueprintCallable, Category = "News")
	FString GetNewsSubject();

	UFUNCTION(BlueprintCallable, Category = "News")
	ENewsType GetNewsType();

	UFUNCTION(BlueprintCallable, Category = "News")
	void SetNewsType(ENewsType type);
};
