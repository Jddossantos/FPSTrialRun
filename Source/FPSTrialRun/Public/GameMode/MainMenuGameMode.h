// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Logging/StructuredLog.h"
#include "UIMenus/MainMenuUI.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual void StartPlay() override;

	//User Widget class
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	//User Widget (MainMenu)
	UPROPERTY()
	UUserWidget* MainMenuWidget;
};
