// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectibles/FPSCollectible.h"

// Sets default values
AFPSCollectible::AFPSCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initiaizing components
	if (!CollisionComponent) 
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSCollectible::BeginOverlap);
		CollisionComponent->InitSphereRadius(50.0f);
		RootComponent = CollisionComponent;
	}
}

// Called when the game starts or when spawned
void AFPSCollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSCollectible::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnCollect();
}

void AFPSCollectible::OnCollect()
{
	UE_LOG(LogTemp, Warning, TEXT("Collectible: OnCollect called"));
}

