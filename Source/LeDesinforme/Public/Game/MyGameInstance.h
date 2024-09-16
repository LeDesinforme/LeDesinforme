#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"


UCLASS()
class LEDESINFORME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

private:
	int m_score;
	
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void SetScore(int _newScore);
	UFUNCTION(BlueprintCallable, Category = "Data")
	int GetScore();
};
