// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FPSGameMode.h"

void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//Bool testing into output
	//this is a way to test/debug code to make sure it goes through correctly
	int test = 1;
	bool boolTest = true;
	UE_LOG(LogTemp, Warning, TEXT("Starting FPS Map %i, TestBool %d, StringText: %s"), boolTest, test, TEXT("Succeed"));

	//Displays a debug message on screen for five seconds.
	//The -1 "Key" value arguement prevents the message from being updated or refreshed.
	//1. To print to the screen
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FPSGameMode Initialized!"));

	//2. To print to output
	//UE_LOG(LogTemp, Warning, TEXT("FPSGameMode Started!"));

	//3. Modern way to printing without format specifiers
	//UE_LOGFMT(LogTemp, Warning, "FPSGameMode Started v.2!");					 //this is using the "Logging/StructuredLog.h" header file
	//UE_LOGFMT(LogTemp, Warning, "Test: {0}, TestBool: {1}", test, boolTest);
}