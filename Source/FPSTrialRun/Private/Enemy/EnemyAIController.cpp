// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	//Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!PawnSensing) {
		PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//Run Behavior tree at begin play
	RunBehaviorTree(StartingBehaviorTree);

	//If looking for pawn
	if (PawnSensing) 
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAIController::OnSeePawn);
	}
}

void AEnemyAIController::OnSeePawn(APawn* PlayerPawn)
{
	//Casting to FPSCharacter for spotting
	AFPSCharacter* player = Cast<AFPSCharacter>(PlayerPawn);
	if (!player) return;	//if no player, return

	//Setting the flag to true if play has been spotted
	SetCanSeePlayer(true, player);

	//Run timer
	RunTriigerableTimer();
}

void AEnemyAIController::SetCanSeePlayer(bool SeePlayer, UObject* Player)
{
	//Blackboard pointer, Gets Blackboard component
	UBlackboardComponent* bb = GetBlackboardComponent();

	//Setting value as bool, false if they cannot see player, true if they can
	bb->SetValueAsBool(FName("Can See Player"), SeePlayer);
	if (SeePlayer) 
	{
		//Setting object as player if spotted
		bb->SetValueAsObject(FName("Player Target"), Player);
	}
}

void AEnemyAIController::RunTriigerableTimer()
{
	//Calling Timer
	GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);

	//Reseting the timer
	FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, GetPawn());
	GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle, FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);
}
