// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		//Use a sphere as a simple collision representation
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

		//Sets the sphere's collision radius
		CollisionComponent->InitSphereRadius(0.05f);

		//Setting the profile name to Projectile
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

		//Event called when component hits something
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHitSomething);

		//Sets the root component to be the collision component
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		//Use this Component to drive this projectile's movement
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = BulletSpeed;
		ProjectileMovementComponent->MaxSpeed = BulletSpeed;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("/Game/Assets/Mesh/Sphere.Sphere"));
		if (SphereMeshAsset.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(SphereMeshAsset.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial>SphereMaterial(TEXT("/Game/Material/M_Bullet.M_Bullet"));
		if (SphereMaterial.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(SphereMaterial.Object, ProjectileMeshComponent);
		}

		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	//Deleting the projectile after 3 seconds
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Function that initializes the projectile's velocity in the shoot direction.
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	//1. FVector ShootDirection: Pass by value, least efficient (Duplicates) TRY NOT TO DO THIS
	//2. FVector* ShootDirection: Pass by memory, save these situations where you will need to keep using a pointer (memory leak possibilites, use it if you are already using a pointer. can also be changed)
	//3. FVector& ShootDirection: Pass by reference, memory: Someone can change it's content. Basically out.
	//4. const FVector& ShootDirection: Pass by ref, memory: we can't directly change the parameter

	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * ShootDirection;
}

//Function that is called when projectile hiut's something
void AFPSProjectile::OnHitSomething(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		Destroy();
	}
}

