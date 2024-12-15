// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HUD/FPSButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	//Title text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	//Play text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayText;

	//Quit text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;

	//Play Button
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	//Quit Button
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	//Function for when play button is clicked
	UFUNCTION()
	void OnPlayButtonClicked();

	//Function for when the quit button is clicked
	UFUNCTION()
	void OnQuitButtonClicked();
};
