// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEDESINFORME_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSettings")
	int currentScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSettings")
	int highScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSettings")
	float timerDefaultValue = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSettings")
	float timer = 0.f;

public:
	AMyGameMode();

public:
	void BeginPlay() override;
	void Tick(float _deltaSeconds) override;
	
	UFUNCTION(BlueprintCallable, Category = "GameSetting")
	static void SetFullScreen(bool bIsFullScreen);

	UFUNCTION(BlueprintCallable, Category = "GameSettings")
	void NewRound();
	UFUNCTION(BlueprintCallable, Category = "GameSettings")
	void UpdateHighScore(int _score);
	// Check if score > high score and if yes update high score
	void CheckHighScore();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void SaveHighScore();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void LoadHighScore();
};
