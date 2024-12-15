// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FPSGameUI.h"

void UFPSGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);		//Calling Set health bar function
	SetScoreText(UIScore);		//Calling Set score text function


	TimerSeconds = 0;		//Seconds are set to 0
	TimerHandle = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UFPSGameUI::SetTimerText, 1.0f, true);

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
	if (!ScoreText) return;	//If no Score Text then return

	UIScore += amount;		//Score adds amount
	ScoreText->SetText(FText::FromString("Score: " + FString::FromInt(UIScore)));	//Setting Score Text
}

void UFPSGameUI::SetTimerText()
{
	if (!TimerText)	return;	//If no Timer Text then return

	TimerSeconds++;	//Add to seconds
	int minutes = TimerSeconds / 60;	//Minutes are divided by 60
	int seconds = TimerSeconds % 60;
	TimerText->SetText(FText::FromString("Timer: " + FString::FromInt(minutes) + ":" + FString::FromInt(seconds)));		//Setting Timer text
}
