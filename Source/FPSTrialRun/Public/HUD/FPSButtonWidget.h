// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FPSButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API UFPSButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta= (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	//Function for setting the Text
	UFUNCTION()
	void SetText(int value);

	//Function for On button clicked
	UFUNCTION()
	void OnButtonClick();

private:
	int num = -1;
};
