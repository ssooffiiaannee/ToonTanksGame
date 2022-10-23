// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f); //ToTarget.Rotation();
	// LookAtRotation.Pitch = 0.f;
	// LookAtRotation.Roll = 0.f;

	// 
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f
		)
	);
}

void ABasePawn::Fire()
{	
	// ####### Debug #################
	// DrawDebugSphere(GetWorld(), 
    //     ProjectileSpawnPoint->GetComponentLocation(),
    //     10.f,
    //     12,
    //     FColor::Red,
    //     false,
    //     3.f
    // );

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, 
										ProjectileSpawnPoint->GetComponentLocation(), 
										ProjectileSpawnPoint->GetComponentRotation()
										);
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual/sound effects
	if(DeathParticles){
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
		if(DeathSound)
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		
		if(DeathCameraShakeClass != nullptr)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}


// Called when the game starts or when spawned
// void ABasePawn::BeginPlay()
// {
// 	Super::BeginPlay();
	
// }

// // Called every frame
// void ABasePawn::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);

// 	// UE_LOG(LogTemp, Warning, TEXT("The move value is : %f"), value);

//     // FVector DeltaLocation(0.f);
//     // // double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
//     // DeltaLocation.X = 1;//value * speed * DeltaTime;
//     // AddActorLocalOffset(DeltaLocation);
// }

// void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
//     // bind to the move forward axis mapping
//     Super::SetupPlayerInputComponent(PlayerInputComponent);

//     PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABasePawn::Move);
// }

// void ABasePawn::Move(float value)
// {
//     UE_LOG(LogTemp, Warning, TEXT("The move value is : %f"), value);

//     FVector DeltaLocation(0.f);
//     // double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
//     DeltaLocation.X = 1;//value * speed * DeltaTime;
//     AddActorLocalOffset(DeltaLocation);
// }

