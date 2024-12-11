// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectile/FPSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
//#include "PhysicsInterfaceDeclaresCore.h"
#include "FPSCharacter.generated.h"

//class UInputMappingContext;
//class UInputAction;

UCLASS()
class FPSTRIALRUN_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool bIsFiring;			//Flag for checking if the plauyer is firing their weapon
	float FireRate = 0.1f;	//Float to set for the weapons FireRate
	FTimerHandle FireTimerHandle;	//Fire Timer to simulate the weapon firing at the pace of the fire rate

	//First-Person Mesh, visible only to the owning player
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	//FPS Camera
	UPROPERTY(VisibleAnyWhere, Category = "Camera")
	UCameraComponent* FPSCameraComponent;

	//Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffest;

	//Projectile class
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	//Scene Component to attach the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USceneComponent* WeaponAttachmentPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AFPSWeapon> WeaponClass;

	//currently equipped weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	AFPSWeapon* CurrentWeapon;

	//Handles input for moving forward and backwards
	UFUNCTION()
	void MoveForward(float value);

	//Handles input for moving left and right
	UFUNCTION()
	void MoveLR(float value);

	//Sets Jump flag when key is pressed (true)
	UFUNCTION()
	void StartJump();
	
	//Clears Jump flag when key is released (false)
	UFUNCTION()
	void EndJump();
	
	//Function that handles Spawning projectiles.
	UFUNCTION()
	void Fire();

	//Function that handles the start of the player firing their weapon
	UFUNCTION()
	void StartFire();

	//Function that stops the firing of the weapon after the player does
	UFUNCTION()
	void StopFire();

};
