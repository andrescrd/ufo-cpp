// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class UFO_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int enemyCounter = 0;
	float initialTimeToSpawm;

public:
	FTimerHandle spawnerTimerHandle;
	FTimerHandle veloctyTimerHandle;

	UPROPERTY(EditAnywhere) float timeToSpawn = 5;
	UPROPERTY(EditAnywhere) float timeToIncrementSpawnVelocity = 10;
	UPROPERTY(EditAnywhere) int maxEnemySpawned = 10;
	UPROPERTY(EditAnywhere) FVector radio = FVector(500, 500, 0);
	UPROPERTY(EditAnywhere) float factorOfIncrement = 2;

	UPROPERTY(EditAnywhere, meta = (UIMin = '1')) int minEnemySpawnerAtSameTime = 1;
	UPROPERTY(EditAnywhere, meta = (UIMin = '1')) int maxEnemySpawnerAtSameTime = 6;

	UPROPERTY(EditAnywhere) TSubclassOf<class AActor> actorToSpawn;

	void SpawnerTimer();
	void StopSpawner();
	void IncrementVelocityOfSpawn();
};