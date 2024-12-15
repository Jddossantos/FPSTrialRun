// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/GameOverTrigger.h"

// Sets default values
AGameOverTrigger::AGameOverTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize box collider
	GameOverTriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("GameOverTriggerCollider"));
	RootComponent = GameOverTriggerCollider;

	//Set overlap event to trigger on TransitionToGameOverLevel
	GameOverTriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &AGameOverTrigger::TransitionToGameOverLevel);
}

// Called when the game starts or when spawned
void AGameOverTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameOverTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Function for GameOver Level Transition
void AGameOverTrigger::TransitionToGameOverLevel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Load the GameOver level
	UGameplayStatics::OpenLevel(this, FName(TEXT("GameOver")));
}

