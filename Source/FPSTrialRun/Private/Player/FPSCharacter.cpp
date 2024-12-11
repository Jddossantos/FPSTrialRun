// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSCharacter.h"
//#include "Weapon/FPSWeapon.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
	:bIsFiring(false)		//Initializing the bool and setting it to false
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Similar Unity Instantiate but only for constructors
	if (!FPSCameraComponent) 
	{
		//Creating a default subobject (Camera) and giving it a name
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

		//Attatching the CameraComponent to the CapsuleComponent
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

		//Setting it's height +  the base height
		FPSCameraComponent->SetRelativeLocation(FVector(10.0f, 0.0f, 10.0f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;		//Enabling the pawn to control camera rotation
	}

	if (!FPSMesh) 
	{
		//Creating new mesh and assigning it to FPSMesh (owning player)
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

		//Attatching the camera comonent to the FPSMesh
		FPSMesh->SetupAttachment(FPSCameraComponent);

		//Diabling some environment shadowning to preserve illusion of having a single mesh
		FPSMesh->bCastDynamicShadow = false;			//Setting the CastDynamicShadow to false
		FPSMesh->CastShadow = false;					//Setting the CastShadow to false
	}

	/*if (!WeaponAttachmentPoint)
	{
		//Creating the weapon attachment point as a scene component
		WeaponAttachmentPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachmentComponent"));
		WeaponAttachmentPoint->SetupAttachment(FPSCameraComponent);	//Attach to player character
		WeaponAttachmentPoint->SetRelativeLocation(FVector(50.0f, 0.0f, 50.0f));
	}*/

	GetMesh()->SetOwnerNoSee(true);

	UE_LOG(LogTemp, Warning, TEXT("FPSCharacter Constructor called!"));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("We are using FPSCharacter."));

	// Spawn and attach the weapon
	/*if (WeaponClass)
	{
		CurrentWeapon = GetWorld()->SpawnActor<AFPSWeapon>(WeaponClass);
		if (CurrentWeapon && WeaponAttachmentPoint)
		{
			CurrentWeapon->AttachToComponent(WeaponAttachmentPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}*/
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Set up "Movement" bindings (front and back)
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	//Set up "Movement" bindings (left and right)
	PlayerInputComponent->BindAxis("MoveLR", this, &AFPSCharacter::MoveLR);

	//Set up "Looking" bindings (Left/Right)
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	//Set up "Looking" bindings (Up/Down)
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	//Set Up "Action/Jump" bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);

	//Start Firing
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::StartFire);
	//Stop Firing
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::StopFire);
}

void AFPSCharacter::MoveForward(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moving Forward : %f"), value);
	
	//1. Unreal tutorial way
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	//2. Looking through documention for another solution
	//Finding out which way is "Forward" and record that the player wants to move in that direction
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveLR(float value)
{
	//1. Unreal tutorial way
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	//2. Looking through documention for another solution
	//Finding out which way is "Right" and record that the player wants to move in that direction
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

//Fire function for spawning projectiles
void AFPSCharacter::Fire()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("PEW PEW PEW"));

	//If not ProjectileClass, return
	if (!ProjectileClass)	return;

	//Get Camera transform (location and rotation
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	//Setting the MuzzleOffset to spawn projectiles slightly in front of the camera
	MuzzleOffest.Set(400.0f, 0.0f, 20.0f);

	//Transform MuzzleOffset from the camera space to world space
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffest);

	//Skew the aim to be slightly upwards.
	FRotator MuzzleRotation = CameraRotation;
	//MuzzleRotation.Pitch += 10.0f;
	//MuzzleRotation.Yaw -= 3.0f;

	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	//Spawning the projectile at the muzzle
	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

	if (!Projectile) return;

	//Set the projectile's initial trajactory
	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);
}

void AFPSCharacter::StartFire()
{
	if (bIsFiring) return;	//To prevent dublicate calls
	bIsFiring = true;		//Sets the flag to true

	//Calls Fire function 
	Fire();
	//Starts Fire Rate timer (0.1f) to simulate a fire rate
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AFPSCharacter::Fire, FireRate, true);
}

void AFPSCharacter::StopFire()
{
	bIsFiring = false;

	//Stoping the firing timer
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

