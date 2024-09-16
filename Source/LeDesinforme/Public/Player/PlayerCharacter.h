// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/Item.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Employee/Employee.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UENUM()
enum ECameraState
{
	Default,
	LookScreen
};

UCLASS()
class LEDESINFORME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	TEnumAsByte<ECameraState> CameraState;

protected:
	virtual void BeginPlay() override;

	// Actions Input Functions
	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);	

	void OnFocusStart(const FInputActionValue& value);

	void OnFocusEnd(const FInputActionValue& value);

	void StopAction(const FInputActionValue& value);

	void SelectAction(const FInputActionValue& value);

	void MenuAction(const FInputActionValue& value);

	void ReportAction(const FInputActionValue& value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> cameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> playerCamera;

	// Input
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> defaultMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> moveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> lookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> focusAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> stopAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> selectAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> menuAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> reportAction;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<USoundBase> lookingSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<USoundBase> winSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<USoundBase> loseSound = nullptr;

private:
	bool isFocused;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float targetFOV;        

	float currentFOV;       

	float FOVInterpSpeed;  

	UPROPERTY(EditAnywhere, Category = "Focus", meta = (AllowPrivateAccess = "true"))
	float focusSpeed;

	float BobbingAmplitude;    
	float BobbingFrequency;    
	float BobbingElapsedTime;  

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	bool bIsWalking;           

	UPROPERTY(EditAnywhere, Category = "Focus")
	TObjectPtr<AItem> focusedObject;

	UFUNCTION()
	void DetectObejctsInView();

private:
	FVector originalCameraLocation;
	FRotator originalCameraRotation;
	FRotator originalControlRotation;

	class UAIPerceptionStimuliSourceComponent* m_stimulusSourceComponent = nullptr;
	void SetupStimulusSource();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StartLookScreen();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void ExitLookScreen();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CallMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerGameOver();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerGameWin();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	TObjectPtr<AEmployee> employeeOnFocused;

	UFUNCTION(BlueprintCallable, category = "Report")
	void ReportEmployee();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	bool isSuccessfulReport;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
