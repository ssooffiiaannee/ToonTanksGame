// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	public:
		ATank();
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		void HandleDestruction();

		APlayerController* GetTankPlayerController() const {return TankPlayerController;}

		bool bAlive = true;
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		

	private:
		UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent *springArmComponent;

		UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent *cameraComponent;

		void Move(float value);
		void Turn(float value);

		UPROPERTY(EditAnywhere, Category = "Movement", meta=(AllowPrivateAccess="true"))
		double speed = 30;
		
		UPROPERTY(EditAnywhere, Category = "Movement", meta=(AllowPrivateAccess="true"))
		double TurnRate = 75;

		APlayerController *TankPlayerController;
};
