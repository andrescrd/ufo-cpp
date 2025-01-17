#include "Spawner.h"
#include "TimerManager.h"
#include "Engine/World.h"

ASpawner::ASpawner()
{
	initialTimeToSpawm = timeToSpawn;
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(spawnerTimerHandle, this, &ASpawner::SpawnerTimer, timeToSpawn, true);
	GetWorldTimerManager().SetTimer(veloctyTimerHandle, this, &ASpawner::IncrementVelocityOfSpawn, timeToIncrementSpawnVelocity, true);
}

void ASpawner::SpawnerTimer()
{
	if (maxEnemySpawned == 0 || enemyCounter <= maxEnemySpawned)
	{
		for (int i = 0; i < FMath::RandRange(minEnemySpawnerAtSameTime, maxEnemySpawnerAtSameTime); i++)
		{
			float x = FMath::RandRange(-radio.X, radio.X);
			float y = FMath::RandRange(-radio.Y, radio.Y);
			float z = FMath::RandRange(-radio.Z, radio.Z);

			FVector location = GetActorLocation() + FVector(x, y, z);
			GetWorld()->SpawnActor<AActor>(actorToSpawn, location, FRotator(0, 0, 0));

			enemyCounter++;
		}
	}
	else
	{
		StopSpawner();
	}
}

void ASpawner::StopSpawner()
{
	GetWorldTimerManager().ClearTimer(spawnerTimerHandle);
	GetWorldTimerManager().ClearTimer(veloctyTimerHandle);
	enemyCounter = 0;
	timeToSpawn = initialTimeToSpawm;
}

void ASpawner::IncrementVelocityOfSpawn()
{
	timeToSpawn = FMath::Clamp(timeToSpawn - 0.1f * factorOfIncrement, 0.3f, timeToSpawn);
	GetWorldTimerManager().ClearTimer(spawnerTimerHandle);
	GetWorldTimerManager().SetTimer(spawnerTimerHandle, this, &ASpawner::SpawnerTimer, timeToSpawn, true);
}
