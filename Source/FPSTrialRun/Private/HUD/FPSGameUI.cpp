// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FPSGameUI.h"

void UFPSGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);		//Calling Set health bar function
	SetScoreText(0);		//Calling Set score text function

	/*if (ButtonWidgetPrefab) {
		for (int i = 0; i < 4; i++) {
			UUserWidget* widget = CreateWidget(this, ButtonWidgetPrefab);
			ButtonContainer->AddChildToVerticalBox(widget);

			UButtonWidget* button = Cast<UButtonWidget>(widget); // Basically GetComponent() in Unity
			button->SetText(i);
		}
	}*/
}

//Function to set health bar by passing through the percentage
void UFPSGameUI::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

//Function for setting the score text by passing in the score amount
void UFPSGameUI::SetScoreText(int amount)
{
	if (!ScoreText) return;

	UIScore += amount;
	ScoreText->SetText(FText::FromString("Score: " + FString::FromInt(UIScore)));
}
