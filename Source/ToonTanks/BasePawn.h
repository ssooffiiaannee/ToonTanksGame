// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();	

	// UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly) // visible only when we instance the object
	// int32 VisibleInstanceOnlyInt = 11;

	// UPROPERTY(VisibleDefaultsOnly)
	// int32 VisibleDefaultsOnlyInt = 33;

	// UPROPERTY(EditDefaultsOnly)
	// int32 EditDefaulstOnlyInt = 5;

	// UPROPERTY(EditInstanceOnly)
	// int32 EditInstanceOnlyInt = 44;

// protected:
// 	// Called when the game starts or when spawned
// 	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent* CapsuleComp; // forward declaration
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	class USceneComponent* ProjectileSpawnPoint;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Super duper var", meta=(AllowPrivateAccess="true")) // visible and we cannot edit this property
	// int32 VisibleAnywhereInt = 12;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Super duper var", meta=(AllowPrivateAccess="true"))
	// int32 EditAnywhereInt = 22;

	UPROPERTY(EditAnywhere, Category = "Combat",  meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();
// public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input : input handling
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// void Move(float);
};
