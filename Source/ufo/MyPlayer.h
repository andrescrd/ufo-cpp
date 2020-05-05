// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayer.generated.h"

UCLASS()
class UFO_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FTimerHandle AbductionTimerHandle;
	FTimerHandle FastBoostTimerHandle;
	FTimerHandle StopFastBoostTimerHandle;

	// UPROPERTY(VisibleAnywhere)	class UCameraComponent *camera;
	UPROPERTY(VisibleAnywhere)	class UStaticMeshComponent *Body;
	UPROPERTY(VisibleAnywhere)	class UCapsuleComponent *AbductionZone;
	UPROPERTY(VisibleAnywhere)	bool HasFastBoost;
	UPROPERTY(VisibleAnywhere)	bool AbductionOn;

	UPROPERTY(EditAnywhere)	float Velocity = 600;
	UPROPERTY(EditAnywhere)	float RotationVelocity = 80;
	UPROPERTY(EditAnywhere)	float FastBoostForce = 50;
	UPROPERTY(EditAnywhere)	float FastBoostDuration = 2.5;
	UPROPERTY(EditAnywhere) float damage = 10;

	// virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void MoveVertical(float Value);
	void Rotate(float Value);

	void StartFastBoost();
	void StopFastBoost();
	void FastBoostTimer();

	void StartAbduction();
	void StopAbduction();
	void AbductionTimer();

	void StartFire();

	UFUNCTION()
	void OnAbductionZoneBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnAbductionZoneEndOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
};
