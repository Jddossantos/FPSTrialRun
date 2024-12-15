// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EndGameDoor.h"
#include "Player/FPSCharacter.h"
#include "EndGameTrigger.generated.h"

UCLASS()
class FPSTRIALRUN_API AEndGameTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGameTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Box Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollider;
	
	//Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PressurePlate;

	//Fuction for player collision to check if the player is overlapping with the collider
	UFUNCTION()
	void OnPlayerCollision(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Reference to EndGameDoor class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndGameDoor")
	AEndGameDoor* EndGameDoor;
};
