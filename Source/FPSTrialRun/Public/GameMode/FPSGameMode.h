// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/FPSGameUI.h"
#include "FPSGameMode.generated.h"		//This line of code has to be last

/**
 * 
 */

UCLASS()
class FPSTRIALRUN_API AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere)
	int RequiredScore = 10;
};
