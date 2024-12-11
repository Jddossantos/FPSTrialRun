// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FPSButtonWidget.h"

void UFPSButtonWidget::SetText(int value)
{
	if (!Button || !ButtonText) return;	//If no Button or Button text, return

	num = value;
	ButtonText->SetText(FText::FromString("Button: " + FString::FromInt(num)));	
	Button->OnClicked.AddDynamic(this, &UFPSButtonWidget::OnButtonClick);		//Event on click to be called
}

void UFPSButtonWidget::OnButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked: %d"), num);
}
