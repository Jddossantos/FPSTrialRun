// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUD/FPSGameUI.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EndGameDoor.generated.h"

UCLASS()
class FPSTRIALRUN_API AEndGameDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGameDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsDestroyed;

	//Box Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollider;

	//Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorMesh;

	//Destroy door function
	UFUNCTION()
	void DestroyDoor();
};
