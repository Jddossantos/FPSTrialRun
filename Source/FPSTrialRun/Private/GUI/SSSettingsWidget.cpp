// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/SSSettingsWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSSettingsWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(700.0f, 300.0f);		//FMargin is used for padding (horizontal, vertical)
	const FMargin ButtonPadding = FMargin(50.0f, 30.0f);		//Button padding

	const FText TitleText = FText::FromString("FPS Trial Run");	//Title Text 
	const FText ResumeText = FText::FromString("Resume");		//Resume Text
	const FText SoundText = FText::FromString("Sound");			//Sound Text
	const FText QuitText = FText::FromString("Quit");			//Quit Text

	FSlateFontInfo TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbassedText");	//Title font from Unreal
	TitleTextStyle.Size = 60.0f;	//Title Font size

	FSlateFontInfo ButtonTextStyle = TitleTextStyle;			//Button text style is set to the same as TitleTextStyle
	ButtonTextStyle.Size = 40.0f;	//Button Font size is a bit smaller

	ChildSlot
	[
		//New Overlay
		SNew(SOverlay)
		+SOverlay::Slot()		//Adds a child object
		.HAlign(HAlign_Fill)	//Horizontal fill for background
		.VAlign(VAlign_Fill)	//Vertical fill for background
		[
			SNew(SImage)		//Adds an image
			.ColorAndOpacity(FColor::Black)	//Sets the color to black
		]
		+SOverlay::Slot()		//Adds a child object
		.HAlign(HAlign_Fill)	//Horizontal fill
		.VAlign(VAlign_Fill)	//Vertical fill
		.Padding(ContentPadding)
		[
			//Title Text
			SNew(SVerticalBox)	//New Vertical Box
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)		//New text block
				.Font(TitleTextStyle)	//TitleTextStyle for Font
				.Text(TitleText)		//Displays Title text
				.Justification(ETextJustify::Center)	//Centers text
			]
			//Resume Button
			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)	//New Button
				.OnClicked(this, &SSSettingsWidget::OnResumeClicked)	//On click event
				[
					SNew(STextBlock)		//New text block
					.Font(ButtonTextStyle)	//ButtonTextStyle for Font
					.Text(ResumeText)		//Displays Resume text
					.Justification(ETextJustify::Center)	//Centers text
				]
			]
			//Sound Button
			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)	//New Button
				.OnClicked(this, &SSSettingsWidget::OnSoundClicked)	//On click event
				[
					SNew(STextBlock)		//New text block
					.Font(ButtonTextStyle)	//ButtonTextStyle for Font
					.Text(SoundText)		//Displays Sound text
					.Justification(ETextJustify::Center)	//Centers text
				]
			]
			//Quit Button
			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)	//New Button
				.OnClicked(this, &SSSettingsWidget::OnQuitClicked)	//On click event
				[
					SNew(STextBlock)		//New text block
					.Font(ButtonTextStyle)	//ButtonTextStyle for Font
					.Text(QuitText)			//Displays Sound text
					.Justification(ETextJustify::Center)	//Centers text
				]
			]
		]

	];
	
}
FReply SSSettingsWidget::OnResumeClicked() const
{
	//Checking if HUD is valid
	if (OwningHUD.IsValid())	
	{
		OwningHUD->RemoveSettingsMenu();	//Call Remove settings menu
	}
	return FReply::Handled();
}
FReply SSSettingsWidget::OnSoundClicked() const
{
	return FReply::Handled();
}
FReply SSSettingsWidget::OnQuitClicked() const
{
	//Checking if HUD is valid
	if (OwningHUD.IsValid())	
	{
		//If player clicks "Quit"
		if (APlayerController* PC = OwningHUD->PlayerOwner)		
		{
			PC->ConsoleCommand("quit");		//Quit out of the level
		}
	}
	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
