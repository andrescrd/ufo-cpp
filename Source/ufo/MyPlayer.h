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
	FTimerHandle fastBoostTimerHandle;
	FTimerHandle stopFastBoostTimerHandle;

	// UPROPERTY(VisibleAnywhere)	class UCameraComponent *camera;
	UPROPERTY(VisibleAnywhere)	class UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere)	class UCapsuleComponent* AbductionZone;
	
	UPROPERTY(VisibleAnywhere)	bool hasFastBoost;
	UPROPERTY(VisibleAnywhere)	bool abductionOn;

	UPROPERTY(EditAnywhere)	float velocity = 600;
	UPROPERTY(EditAnywhere)	float rotationVelocity = 80;
	UPROPERTY(EditAnywhere)	float fastBoostForce = 50;
	UPROPERTY(EditAnywhere)	float fastBoostDuration = 2.5;
	UPROPERTY(EditAnywhere) float damage = 10;
	UPROPERTY(EditAnywhere) float shootForce = 500;

	// virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	void MoveVertical(float value);
	void Rotate(float value);

	void StartFastBoost();
	void StopFastBoost();
	void FastBoostTimer();

	void StartAbduction();
	void StopAbduction();
	void AbductionTimer();

	void StartFire();

	UFUNCTION()
	void OnAbductionZoneBeginOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnAbductionZoneEndOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex);
};
