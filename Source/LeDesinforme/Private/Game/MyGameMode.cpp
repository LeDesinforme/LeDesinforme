// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MyGameMode.h"

#include "Game/MyGameInstance.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

AMyGameMode::AMyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set the default pawn class to be the player character

	// FIntPoint Resolution = GEngine->GetGameUserSettings()->GetScreenResolution();
	// UE_LOG(LogTemp, Warning, TEXT("Current Resolution: %d %d"), Resolution.X, Resolution.Y);

	// GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	// GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1920, 1080));
	// GEngine->GetGameUserSettings()->ApplySettings(true);
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetGameInstance());
	currentScore = gameInstance->GetScore();
	LoadHighScore();
	timer = timerDefaultValue;
}

void AMyGameMode::Tick(float _deltaSeconds)
{
	Super::Tick(_deltaSeconds);

	// UE_LOG(LogTemp, Warning, TEXT("CURRENT ROUND: %d"), currentScore);
	timer -= _deltaSeconds;

	if (timer <= 0.0f)
	{
		NewRound();
	}
}

void AMyGameMode::SetFullScreen(bool bIsFullScreen)
{
	// GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	// GEngine->GetGameUserSettings()->ApplySettings(bIsFullScreen);
}

void AMyGameMode::NewRound()
{
	timer = timerDefaultValue;
	currentScore++;
	CheckHighScore();
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetGameInstance());
	gameInstance->SetScore(currentScore);
	UGameplayStatics::OpenLevel(this, "GameLevel");
}

void AMyGameMode::UpdateHighScore(int _score)
{
	highScore = _score;
}

void AMyGameMode::CheckHighScore()
{
	if (currentScore > highScore)
	{
		UpdateHighScore(currentScore);
		SaveHighScore();
	}
}

void AMyGameMode::SaveHighScore()
{
	FString directory = FPaths::ProjectContentDir() + TEXT("Scores/");
	FString filePath = directory + TEXT("highscore.txt");

	// Ensure the directory exists
	IFileManager& fileManager = IFileManager::Get();
	if (!fileManager.DirectoryExists(*directory))
	{
		fileManager.MakeDirectory(*directory);
	}

	// Format the high score data into a string
	FString scoreToSave;
	scoreToSave += FString::Printf(TEXT("High Score: %d"), highScore) + LINE_TERMINATOR;

	// Save the formatted string to the file
	if (FFileHelper::SaveStringToFile(scoreToSave, *filePath))
	{
		UE_LOG(LogTemp, Log, TEXT("High score saved to: %s"), *filePath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to save high score to: %s"), *filePath);
	}
}

void AMyGameMode::LoadHighScore()
{
	FString directory = FPaths::ProjectContentDir() + TEXT("Scores/");
	FString filePath = directory + TEXT("highscore.txt");

	// Check if the file exists
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*filePath))
	{
		FString loadedHighScore;
        
		// Load the high score from the file
		if (FFileHelper::LoadFileToString(loadedHighScore, *filePath))
		{
			// Remove "High Score: " prefix and convert the remaining number
			FString scoreString;
			loadedHighScore.Split(TEXT("High Score: "), nullptr, &scoreString);

			// Convert string to integer
			highScore = FCString::Atoi(*scoreString);
			UE_LOG(LogTemp, Log, TEXT("Loaded High Score: %d"), highScore);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load high score from: %s"), *filePath);
		}
	}
	else
	{
		// If the file doesn't exist, initialize high score to 0
		highScore = 0;
		UE_LOG(LogTemp, Warning, TEXT("High score file not found. Initialized to 0."));
	}
}
