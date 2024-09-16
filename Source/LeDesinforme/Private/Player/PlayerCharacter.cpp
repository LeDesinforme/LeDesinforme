// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Employee/Employee.h"


#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Item/Computer.h>

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Game/GameManager.h"

// enum class ECameraState
// {
// 	Default,    // Normal mode
// 	LookScreen  // Watching mode
// };
//
// ECameraState CameraState;

#pragma region Constructor

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the Camera components
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 0.0f;
	cameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	// Lock the camera to the character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Only the camera boom should rotate	
	cameraBoom->bUsePawnControlRotation = true;
	playerCamera->bUsePawnControlRotation = false;

	// Set the character rotation to the direction of movement	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
	
	// Default Camera FOV
	targetFOV = 90.f;
	currentFOV = 90.f;
	focusSpeed = 0.3f;

	// Defalut camera state
	CameraState = ECameraState::Default;

	BobbingAmplitude = 8;   
	BobbingFrequency = 15.0f;   
	BobbingElapsedTime = 0.0f;
	bIsWalking = false;

	SetupStimulusSource();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind the input actions
	if (const ULocalPlayer* Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (defaultMapping)
		{
			Subsystem->AddMappingContext(defaultMapping, 0);
		}
	}

	if (playerCamera)
	{
		currentFOV = playerCamera->FieldOfView;
	}
}

#pragma endregion Constructor

#pragma region Player Movement

void APlayerCharacter::Move(const FInputActionValue& value)
{
	FVector2D moveVector = value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, moveVector.X);
		AddMovementInput(RightDirection, moveVector.Y);

	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookVector = value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(lookVector.X);
		AddControllerPitchInput(lookVector.Y);
	}
}

#pragma endregion Player Movement

#pragma region Player_Action

void APlayerCharacter::OnFocusStart(const FInputActionValue& value)
{
	isFocused = true;
	targetFOV = 60.f;
	FOVInterpSpeed = FMath::Abs(currentFOV - targetFOV) * focusSpeed;
}

void APlayerCharacter::OnFocusEnd(const FInputActionValue& value)
{
	isFocused = false;
	targetFOV = 90.f;
	FOVInterpSpeed = FMath::Abs(currentFOV - targetFOV);
}

void APlayerCharacter::StopAction(const FInputActionValue& value)
{
	if (CameraState == ECameraState::LookScreen)
	{
		ExitLookScreen();
	}

	isFocused = false;
}

void APlayerCharacter::SelectAction(const FInputActionValue& value)
{
	if (isFocused && CameraState != ECameraState::LookScreen && focusedObject)
	{
		CameraState = ECameraState::LookScreen;
		StartLookScreen();
	}
}

void APlayerCharacter::MenuAction(const FInputActionValue& value)
{
	CallMenu();
}

void APlayerCharacter::ReportAction(const FInputActionValue& value)
{
	if (isFocused && employeeOnFocused)
	{
		ReportEmployee();
	}
}

#pragma endregion Player_Action

void APlayerCharacter::DetectObejctsInView()
{
	TObjectPtr<APlayerController> playerController = Cast<APlayerController>(GetController());
	if (playerController == nullptr) return;

	FVector camLocation;
	FRotator camRotation;
	playerController->GetPlayerViewPoint(camLocation, camRotation);

	FVector start = camLocation;
	FVector end = camLocation + (camRotation.Vector() * 800.0f);

	FHitResult hitResult;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);

	bool isHIt = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, collisionParams);
	
	if (isHIt)
	{
		TObjectPtr<AItem> hitItem = Cast<AItem>(hitResult.GetActor());
		TObjectPtr<AEmployee> hitEmpolyee = Cast<AEmployee>(hitResult.GetActor());
		if (hitItem)
		{
			// Selected this item
			focusedObject = hitItem;
			// Debug
			DrawDebugSphere(GetWorld(), hitResult.Location, 10.0f, 12, FColor::Blue, false, 0.2f, 0.5f);
		}

		if (hitEmpolyee)
		{
			employeeOnFocused = hitEmpolyee;
			// Debug
			DrawDebugSphere(GetWorld(), hitResult.Location, 10.0f, 12, FColor::Red, false, 0.2f, 0.5f);
		}

	}
}

#pragma region Player_Watching

void APlayerCharacter::SetupStimulusSource()
{
	m_stimulusSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimulusSourceComponent"));
	if (m_stimulusSourceComponent)
	{
		m_stimulusSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
		m_stimulusSourceComponent->RegisterWithPerceptionSystem();
	}
}

void APlayerCharacter::StartLookScreen()
{
	if (focusedObject == nullptr) return;

	originalCameraLocation = playerCamera->GetComponentLocation();
	originalCameraRotation = playerCamera->GetComponentRotation();
	originalControlRotation = GetControlRotation();

	GetCharacterMovement()->DisableMovement();

	FVector objectLocation = focusedObject->GetActorLocation();
	FVector cameraTargetLocation = objectLocation + FVector(0, 0, 150) + focusedObject->GetActorForwardVector() * -150.0f; 
	FRotator cameraTargetRotation = (objectLocation - cameraTargetLocation).Rotation();

	TObjectPtr<APlayerController> playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		playerController->SetIgnoreLookInput(true);
	}

	playerCamera->SetWorldLocation(cameraTargetLocation);
	playerCamera->SetWorldRotation(cameraTargetRotation);

	TObjectPtr<AComputer> computer = Cast<AComputer>(focusedObject);
	if (computer)
	{
		// Spawn the sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), lookingSound, computer->GetActorLocation());

		computer->CallMessageBox();
	}
}

void APlayerCharacter::ExitLookScreen()
{
	TObjectPtr<AComputer> computer = Cast<AComputer>(focusedObject);
	if (computer)
	{
		computer->HideMessageBox();
	}

	playerCamera->SetWorldLocation(originalCameraLocation);
	playerCamera->SetWorldRotation(originalCameraRotation);

	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		playerController->SetIgnoreLookInput(false);
		playerController->SetControlRotation(originalControlRotation);
	}

	focusedObject = nullptr;
	CameraState = ECameraState::Default;
}

#pragma endregion Player_Watching

void APlayerCharacter::ReportEmployee()
{
	if (employeeOnFocused)
	{
		isSuccessfulReport = employeeOnFocused->BeReported();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, employeeOnFocused.GetName());
		if (isSuccessfulReport)
		{
			PlayerGameWin();
			AGameManager::GameWin();
			return;
		}
		else
		{
			// Play lost sound
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), loseSound, GetActorLocation());

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You failed to report!"));

			PlayerGameOver();

			AGameManager::GameOver();
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CameraState)
	{
	case ECameraState::Default:
		// Change th camera FOV
		if (playerCamera)
		{
			currentFOV = FMath::FInterpTo(currentFOV, targetFOV, DeltaTime, FOVInterpSpeed);
			playerCamera->SetFieldOfView(currentFOV);
		}
		// Detect objects in view with line trace
		if (isFocused)
		{
			DetectObejctsInView();
		}
		break;
	case ECameraState::LookScreen:
		break;
	}
	
	if (isSuccessfulReport)
	{
		// Game win
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You Win!"));
		// Show the win screen
		// Play the win sound
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), winSound, GetActorLocation());
	}

	FVector Velocity = GetVelocity();
	bIsWalking = !Velocity.IsNearlyZero();

	if (bIsWalking)
	{
		BobbingElapsedTime += DeltaTime;
		float BobbingOffset = FMath::Sin(BobbingElapsedTime * BobbingFrequency) * BobbingAmplitude;

		FVector NewTargetOffset = cameraBoom->TargetOffset;
		NewTargetOffset.Z = BobbingOffset;
		cameraBoom->TargetOffset = NewTargetOffset;
	}
	else
	{
		BobbingElapsedTime = 0.0f;
		FVector NewTargetOffset = cameraBoom->TargetOffset;
		NewTargetOffset.Z = 0.0f;
		cameraBoom->TargetOffset = NewTargetOffset;
	}
}

#pragma region Bind_Mapping

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		EnhancedInputComponent->BindAction(focusAction, ETriggerEvent::Started, this, &APlayerCharacter::OnFocusStart);
		EnhancedInputComponent->BindAction(focusAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnFocusEnd);

		EnhancedInputComponent->BindAction(stopAction, ETriggerEvent::Started, this, &APlayerCharacter::StopAction);
		EnhancedInputComponent->BindAction(selectAction, ETriggerEvent::Started, this, &APlayerCharacter::SelectAction);

		EnhancedInputComponent->BindAction(menuAction, ETriggerEvent::Started, this, &APlayerCharacter::MenuAction);
		EnhancedInputComponent->BindAction(reportAction, ETriggerEvent::Started, this, &APlayerCharacter::ReportAction);
	}
}

#pragma endregion Bind_Mapping
