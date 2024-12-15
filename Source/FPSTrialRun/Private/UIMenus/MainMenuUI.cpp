// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMenus/MainMenuUI.h"

void UMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	//If there is a Title Text
	if (TitleText)
	{
		TitleText->SetText(FText::FromString("FPS Trial Run"));	//Setting Title text
	}

	//If there is a Play Text
	if (PlayText)
	{
		PlayText->SetText(FText::FromString("Play"));	//Setting Play Text
	}

	//If there is a Quit Text
	if (QuitText)
	{
		QuitText->SetText(FText::FromString("Quit"));	//Setting Quit Text
	}

	//If there is a PlayButton
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuUI::OnPlayButtonClicked);	//Onclicked event for Play button clicked
	}
	
	//If there is a QuitButton
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuUI::OnQuitButtonClicked);	//OnClicked Event for Quit Button clicked
	}
}

void UMainMenuUI::OnPlayButtonClicked()
{
	//Open up the level
	UGameplayStatics::OpenLevel(this, FName("FPSMap"));
}

void UMainMenuUI::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
