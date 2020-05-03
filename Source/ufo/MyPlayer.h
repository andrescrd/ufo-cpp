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

private:
	bool canUseFastBoost;

public:
	FTimerHandle abductionTimerHandle;
	FTimerHandle fastBoostTimerHandle;

	// UPROPERTY(VisibleAnywhere)	class UCameraComponent *camera;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent *body;

	UPROPERTY(EditAnywhere)
	float velocity = 600;
	UPROPERTY(EditAnywhere)
	float rotationVelocity = 45;
	UPROPERTY(EditAnywhere)
	float fastBoostVelocity = 800;
	UPROPERTY(EditAnywhere)
	float maxDurationFastBoost = 3;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void MoveVertical(float value);
	void Rotate(float value);

	void StartFastBoost();
	void StopFastBoost();
	// void FastBoostTimer();

	void StartAbduction();
	void StopAbduction();
	void AbductionTimer();
};
