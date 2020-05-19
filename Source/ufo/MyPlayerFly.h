// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components\RotateAroundActor.h"
#include "MyPlayerFly.generated.h"

UCLASS()
class UFO_API AMyPlayerFly : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPlayerFly();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	FTimerHandle boostTimerHadle;
	bool isInRotationZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere) URotateAroundActor* RotateAroundActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float fastBoostForceCounter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float velocity = 800;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float rotationVelocity = 90;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	float fastBoostForce = 500;

	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	void Rotate(float value);
	void StartBoost();
	void BoostTimer();
	void StopBoost();

	void OnRotationZone(class AActor* other);
	void DeactivateRotation();
};
