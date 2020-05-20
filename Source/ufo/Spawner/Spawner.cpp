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
	if (maxEnemySpawned == 0 || enemyCounter <= maxEnemySpawned )
	{
		float x = FMath::RandRange(-radio.X, radio.X);
		float y = FMath::RandRange(-radio.Y, radio.Y);
		float z = FMath::RandRange(-radio.Z, radio.Z);

		FVector location = GetActorLocation() + FVector(x,y,z);
		GetWorld()->SpawnActor<AActor>(actorToSpawn, location, FRotator(0, 0, 0));

		enemyCounter++;
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
	timeToSpawn = timeToSpawn / factorOfIncrement;
}
