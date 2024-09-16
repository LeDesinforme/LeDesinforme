// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	m_score = 0;
}

void UMyGameInstance::Init()
{
	Super::Init();

	if (GEngine)
	{
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GameInstance Initialized"));
	}
}

void UMyGameInstance::SetScore(int _newScore)
{
	m_score = _newScore;
}

int UMyGameInstance::GetScore()
{
	return m_score;
}
