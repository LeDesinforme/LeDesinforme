// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Components/BoxComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}