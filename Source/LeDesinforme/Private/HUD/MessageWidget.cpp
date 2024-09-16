// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MessageWidget.h"

void UMessageWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
}

FVector2D UMessageWidget::GetHalfScreenSize() const
{
    FVector2D ScreenSize;

    if (GEngine && GEngine->GameViewport)
    {
        GEngine->GameViewport->GetViewportSize(ScreenSize);
    }

    return ScreenSize * 0.5f;
}
