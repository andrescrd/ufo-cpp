// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/Abducible.h"
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
	float abductionMulitply = 100000.0f;

public:
	FTimerHandle abductionTimerHandle;
	FTimerHandle fastBoostTimerHandle;
	FTimerHandle stopFastBoostTimerHandle;

	// UPROPERTY(VisibleAnywhere)	class UCameraComponent *camera;
	UPROPERTY(VisibleAnywhere)	class UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere)	class UCapsuleComponent* AbductionZone;
	UPROPERTY(VisibleAnywhere)	class USphereComponent* Abductor;

	UPROPERTY(VisibleAnywhere)	bool hasFastBoost;
	UPROPERTY(VisibleAnywhere)	bool abductionOn;
	UPROPERTY(VisibleAnywhere)	int abductionCounter = 0;

	UPROPERTY(EditAnywhere)	float velocity = 1000;
	UPROPERTY(EditAnywhere)	float rotationVelocity = 180;
	UPROPERTY(EditAnywhere)	float fastBoostForce = 100;
	UPROPERTY(EditAnywhere)	float fastBoostDuration = 1;
	UPROPERTY(EditAnywhere) float damage = 10;
	UPROPERTY(EditAnywhere) float shootForce = 500;
	UPROPERTY(EditAnywhere) float abductionForce = 8;

	virtual void Tick(float DeltaTime) override;
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
	void Fire(int fireAmount, float fireRadio);

	UFUNCTION()
		void OnAbductorBeginOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	//UFUNCTION()
	//	void OnAbductionZoneEndOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void OnStartFastBoost();
	UFUNCTION(BlueprintImplementableEvent)
		void OnStopFastBoost();
	UFUNCTION(BlueprintImplementableEvent)
		void OnStartAbduction();
	UFUNCTION(BlueprintImplementableEvent)
		void OnStopAbduction();
	UFUNCTION(BlueprintImplementableEvent)
		void OnFire();
};
