// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Item.generated.h"

class UBoxComponent;

UCLASS()
class LEDESINFORME_API AItem : public APawn
{
	GENERATED_BODY()

public:
	AItem();

protected:
	virtual void BeginPlay() override;

private:

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
