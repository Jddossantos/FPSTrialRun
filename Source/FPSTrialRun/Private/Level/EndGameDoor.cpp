// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/EndGameDoor.h"

// Sets default values
AEndGameDoor::AEndGameDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Box Collider
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	//Initialize Static mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

	//Flag to check if the wall is destroyed
	bIsDestroyed = false;
}

// Called when the game starts or when spawned
void AEndGameDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndGameDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEndGameDoor::DestroyDoor()
{
	Destroy();
	bIsDestroyed = true;
}

