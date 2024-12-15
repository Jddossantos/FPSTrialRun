// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "HUD/FPSButtonWidget.h"
#include "FPSGameUI.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API UFPSGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	//Health bar
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	//Score text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	//Timer text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	//Vertical box
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer;

	//Button widget class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UFPSButtonWidget> ButtonWidgetPrefab;

	//Function for Setting the health bar
	UFUNCTION()
	void SetHealthBar(float percentage);

	//Function for setting the score text
	UFUNCTION()
	void SetScoreText(int amount);

	//Function for setting the timer text
	UFUNCTION()
	void SetTimerText();

	int UIScore;
	FTimerHandle TimerHandle;
	int TimerSeconds;
};
