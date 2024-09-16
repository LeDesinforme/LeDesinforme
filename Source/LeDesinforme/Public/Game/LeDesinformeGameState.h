#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LeDesinformeGameState.generated.h"


UCLASS()
class LEDESINFORME_API ALeDesinformeGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int m_currentScore = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int m_highScore = 0;

	FString m_saveFilePath;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true"))
	float timer = 0.f;

public:
	ALeDesinformeGameState();

private:
	virtual void Tick(float _deltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void UpdateCurrentScore(int _score);
	UFUNCTION(BlueprintCallable, Category = "Score")
	void UpdateHighScore(int _score);

	// Check if score > high score and if yes update high score
	void CheckHighScore();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void SaveHighScore();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void LoadHighScore();

	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore();
	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetHighScore();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	float GetTimer();
};
