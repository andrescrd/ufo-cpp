#include "MyEnemyObjective.h"

AMyEnemyObjective::AMyEnemyObjective()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void AMyEnemyObjective::StartAbduction()
{
	UE_LOG(LogTemp, Warning, TEXT("someone try to abductme"));
	FVector currentLocation = GetActorLocation();
	currentLocation.Z += 10;
	AddActorLocalOffset(currentLocation, true);
}

void AMyEnemyObjective::AbductedFail()
{
	UE_LOG(LogTemp, Warning, TEXT("abduction fail"));
}

