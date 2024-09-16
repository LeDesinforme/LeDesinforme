// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEDESINFORME_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool isEmployeeAtDesk = false;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FVector2D GetHalfScreenSize() const;
};