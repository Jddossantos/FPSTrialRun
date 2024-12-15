// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectibles/FPSCollectible.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/FPSHUD.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class FPSTRIALRUN_API ACoin : public AFPSCollectible
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* CoinMeshComponent;

	//Amount of points to be added
	UPROPERTY(EditAnywhere)
	float Points = 5;

	//Rotation rate
	UPROPERTY(EditAnywhere)
	float RotationRate = 100;

	//Collestion Rate
	UPROPERTY(EditAnywhere)
	float OnCollectRotationRate = 1500;

	//Handle Death timer
	FTimerHandle DeathTimerHandle;
	void DeathTimerComplete();
};
