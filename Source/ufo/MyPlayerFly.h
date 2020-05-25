// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/RotateAroundActor.h"
#include "ufo/Interfaces/Healthable.h"
#include "Player/PlayerBase.h"
#include "MyPlayerFly.generated.h"

UCLASS()
class UFO_API AMyPlayerFly : public APlayerBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPlayerFly();

private:
	float initialArmLength;
	float fastBoostForceCounter = 0;
	FTimerHandle boostTimerHadle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class UCameraComponent* Camera;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float distance = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float velocity = 800;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float rotationVelocity = 90;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	float fastBoostForce = 500;

	UPROPERTY(EditAnywhere)	float minAngleRotation = 0;
	UPROPERTY(EditAnywhere)	float maxAngleRotation = -180;
	UPROPERTY(EditAnywhere)	float armLengthVariation = 80;

	// Called every frame
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	void VerticalMovement(float value);
	void Rotate(float value);

	void StartBoost();
	void BoostTimer();
	void StopBoost();


	UFUNCTION()
		void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
