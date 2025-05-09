// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/FPSHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FPSTRIALRUN_API SSSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSSettingsWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AFPSHUD>, OwningHUD)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AFPSHUD> OwningHUD;

	FReply OnResumeClicked() const;
	FReply OnSoundClicked() const;
	FReply OnQuitClicked() const;
};
