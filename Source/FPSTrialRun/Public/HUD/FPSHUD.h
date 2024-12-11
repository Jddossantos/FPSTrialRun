// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GUI/SSSettingsWidget.h"
#include "Engine/Canvas.h"
#include "HUD/FPSGameUI.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	//This will be drawn at the center of the screen
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

public:
	virtual void BeginPlay() override;

	//1. HUD method of making UI (Primary draw call for the HUD)
	virtual void DrawHUD() override;

	//2. Slates method of making UI
	TSharedPtr<class SSSettingsWidget> settingsWidget;
	TSharedPtr<class SWidget> settingsWidgetContainer;

	void ShowSettingsMenu();
	void RemoveSettingsMenu();

	//3. UMG Method of Making UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFPSGameUI> startingGameWidget;

	UPROPERTY()
	UFPSGameUI* gameWidgetContainer;

	void ShowGameMenu(TSubclassOf<UFPSGameUI> newGameWidget);

};
