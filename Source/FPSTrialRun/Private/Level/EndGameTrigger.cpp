// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/EndGameTrigger.h"

// Sets default values
AEndGameTrigger::AEndGameTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Initialize Box Collider
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

    //Initialize Static Mesh
    PressurePlate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlate"));
    PressurePlate->SetupAttachment(RootComponent);

    //Setting the overlap events to trigger on OnPlayerCollision
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEndGameTrigger::OnPlayerCollision);
}

// Called when the game starts or when spawned
void AEndGameTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndGameTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndGameTrigger::OnPlayerCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //Checking if the overlapping actor is the player
    if (OtherActor && OtherActor->IsA(AFPSCharacter::StaticClass()))  //Checking If the OtherActor is the player character
    {
        if (EndGameDoor)
        {
            EndGameDoor->Destroy();
            UE_LOG(LogTemp, Warning, TEXT("EndGameDoor destroyed"));
        }
    }
}