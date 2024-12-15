// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectibles/Coin.h"

ACoin::ACoin()
{
	//Setting this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CoinMeshComponent) {
		CoinMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Coin_1"));
		CoinMeshComponent->SetupAttachment(CollisionComponent);
	}
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));
}

void ACoin::OnCollect()
{
	Super::OnCollect();

	UE_LOG(LogTemp, Warning, TEXT("Coin: OnCollect Called"));

	RotationRate = OnCollectRotationRate;

	//C++ version of delay node
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ACoin::DeathTimerComplete, 0.2f, false);
}

void ACoin::DeathTimerComplete()
{
	AFPSHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
	if (!HUD) return;

	HUD->gameWidgetContainer->SetScoreText(Points);

	Destroy();
}
