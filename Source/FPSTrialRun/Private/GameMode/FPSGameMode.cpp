// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FPSGameMode.h"

void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);



	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FPSGameMode Initialized!"));
}