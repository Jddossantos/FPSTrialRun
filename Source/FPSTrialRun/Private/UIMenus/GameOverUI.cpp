// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMenus/GameOverUI.h"

void UGameOverUI::NativeConstruct()
{
	//If there is a Title Text
	if (TitleText)
	{
		TitleText->SetText(FText::FromString("FPS Trial Run"));	//Setting Title text
	}

	if (MainMenuText)
	{
		MainMenuText->SetText(FText::FromString("MainMenu"));	//Setting Restart Text
	}

	//If there is a Restart Text
	if (RestartText)
	{
		RestartText->SetText(FText::FromString("Restart"));	//Setting Restart Text
	}

	//If there is a Quit Text
	if (QuitText)
	{
		QuitText->SetText(FText::FromString("Quit"));	//Setting Quit Text
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverUI::OnMainMenuButtonClicked);	//OnClicked event for main menu button clicked
	}

	//If there is a RestartButton
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverUI::OnRestartButtonClicked);	//Onclicked event for Restart button clicked
	}

	//If there is a QuitButton
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameOverUI::OnQuitButtonClicked);	//OnClicked Event for Quit Button clicked
	}
}

void UGameOverUI::OnMainMenuButtonClicked()
{
	//Then open up the level
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UGameOverUI::OnRestartButtonClicked()
{
	//open up the level
	UGameplayStatics::OpenLevel(this, FName("FPSMap"));
}

void UGameOverUI::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
