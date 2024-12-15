// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "Player/FPSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Starting Behaviour Tree
	UPROPERTY(EditAnywhere)
	UBehaviorTree* StartingBehaviorTree;

	//Sensing Pawn
	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* PawnSensing;
	
	//Function for player being seen
	UFUNCTION()
	void OnSeePawn(APawn* PlayerPawn);

	//Function for spotting player pawn
	UFUNCTION()
	void SetCanSeePlayer(bool SeePlayer, UObject* Player);

	//Retriggerable timer handle
	FTimerHandle RetriggerableTimerHandle;

	//Timer Delgate
	FTimerDelegate FunctionDelegate;

	//Run Triggerable Delay
	void RunTriigerableTimer();
};
