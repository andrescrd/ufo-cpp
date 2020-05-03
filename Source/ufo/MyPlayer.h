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

FTimerHandle abductionTimerHandle;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent *camera

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent *body

	UPROPERTY(EditAnywhere)
	float velocity;

	UPROPERTY(EditAnywhere)
	float rotationVelocity;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void MoveVertical(float value);
	void Rotate(float value);
	void FastBoost();
	void StartAbduction();
	void StopAbduction();
	void AbductionTimer();
};
