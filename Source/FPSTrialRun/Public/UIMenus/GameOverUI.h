// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HUD/FPSButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	//Title text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	//MainMenu Text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MainMenuText;

	//Restart text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RestartText;

	//Quit text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	//Play Button
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	//Quit Button
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UFUNCTION()
	void OnMainMenuButtonClicked();

	//Function for when play button is clicked
	UFUNCTION()
	void OnRestartButtonClicked();

	//Function for when the quit button is clicked
	UFUNCTION()
	void OnQuitButtonClicked();
};