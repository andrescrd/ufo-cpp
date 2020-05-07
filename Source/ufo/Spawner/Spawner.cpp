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
	if (enemyCounter <= maxEnemySpawned)
	{
		float x = FMath::RandRange(-radio, radio);
		float y = FMath::RandRange(-radio, radio);

		FVector location = FVector::FVector(x, y, GetActorLocation().Z);
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
	timeToSpawn = timeToSpawn / 2;
}
