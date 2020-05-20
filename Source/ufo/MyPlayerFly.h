// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/RotateAroundActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyPlayerFly.generated.h"

UCLASS()
class UFO_API AMyPlayerFly : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPlayerFly();

private: 
	float initialArmLength;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	FTimerHandle boostTimerHadle;
	bool isInRotationZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) URotateAroundActor* RotateAroundActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float fastBoostForceCounter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float velocity = 800;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float rotationVelocity = 90;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	float fastBoostForce = 500;

	UPROPERTY(EditAnywhere)	float minAngleRotation = 0;
	UPROPERTY(EditAnywhere)	float maxAngleRotation = -180;
	UPROPERTY(EditAnywhere)	float armLengthVariation = 80;

	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	void VerticalMovement(float value);
	void Rotate(float value);
	void StartBoost();
	void BoostTimer();
	void StopBoost();
};
