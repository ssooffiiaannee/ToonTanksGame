// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // find the distnace to the tank
    if(InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
    // check to see if the tank is in range

    // if in range, rotate turret toward tank
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
    // GetWorldTimerManager().
}

void ATower::CheckFireCondition()
{   
    if(Tank == nullptr)
    {
        return;
    }

    if(InFireRange() && Tank->bAlive)
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if(Tank){
        float distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        return distance < FireRange ? true:false;
    }
    return false;
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}