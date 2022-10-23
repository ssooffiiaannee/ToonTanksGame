// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
 	
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
// #include "DrawDebugHelpers.h"

ATank::ATank()
{
    springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Text"));
    springArmComponent->SetupAttachment(RootComponent);

    cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Text"));
    cameraComponent->SetupAttachment(springArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // bind to the move forward axis mapping
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    // APlayerController is a child of AController
    TankPlayerController = Cast<APlayerController>(GetController());

    // DrawDebugSphere(GetWorld(), 
    //     GetActorLocation() + FVector(0.f, 0.f, 200.f),
    //     100.f,
    //     12,
    //     FColor::Red,
    //     true,
    //     30.f
    // );
}

void ATank::Move(float value)
{
    // UE_LOG(LogTemp, Warning, TEXT("The move value is : %f"), value);

    FVector DeltaLocation(0.f);
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaLocation.X = value * speed * DeltaTime;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotation.Yaw = value * TurnRate * DeltaTime;
    AddActorLocalRotation(DeltaRotation, true);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController ->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult
        );
        // DrawDebugSphere(GetWorld(), 
        //     HitResult.ImpactPoint, // GetActorLocation() + FVector(0.f, 0.f, 200.f),
        //     25.f,
        //     12,
        //     FColor::Red,
        //     false,
        //     -1.f // single frame
        // );

        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}