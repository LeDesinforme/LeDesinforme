#include "Game/LeDesinformeGameState.h"


ALeDesinformeGameState::ALeDesinformeGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_currentScore = 0;
	m_highScore = 0;

	// Set the path for the high score file
	m_saveFilePath = FPaths::ProjectSavedDir() + TEXT("HighScore.txt");
}

void ALeDesinformeGameState::Tick(float _deltaSeconds)
{
	Super::Tick(_deltaSeconds);

	timer -= _deltaSeconds;
}

void ALeDesinformeGameState::UpdateCurrentScore(int _score)
{
	m_currentScore += _score;
	CheckHighScore();
}

void ALeDesinformeGameState::UpdateHighScore(int _score)
{
	m_highScore = _score;
}

void ALeDesinformeGameState::CheckHighScore()
{
	if (m_currentScore > m_highScore)
	{
		m_highScore = m_currentScore;
		SaveHighScore();
	}
}

void ALeDesinformeGameState::SaveHighScore()
{
	FString highScoreString = FString::FromInt(m_highScore);
	FFileHelper::SaveStringToFile(highScoreString, *m_saveFilePath);
}

void ALeDesinformeGameState::LoadHighScore()
{
	FString loadedHighScore;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*m_saveFilePath))
	{
		if (FFileHelper::LoadFileToString(loadedHighScore, *m_saveFilePath))
		{
			m_highScore = FCString::Atoi(*loadedHighScore);
		}
	}
}

int ALeDesinformeGameState::GetScore()
{
	return m_currentScore;
}

int ALeDesinformeGameState::GetHighScore()
{
	return m_highScore;
}

float ALeDesinformeGameState::GetTimer()
{
	return timer;
}
