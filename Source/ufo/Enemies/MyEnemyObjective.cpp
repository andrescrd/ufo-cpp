#include "MyEnemyObjective.h"
#include "GameFramework/CharacterMovementComponent.h"


AMyEnemyObjective::AMyEnemyObjective()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void AMyEnemyObjective::StartAbductionMode()
{
	UE_LOG(LogTemp, Warning, TEXT("someone try to abductme"));
	/*FVector currentLocation = GetActorLocation();
	currentLocation.Z += 10;

	AddActorLocalOffset(currentLocation, true);*/
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void AMyEnemyObjective::DisableAbductionMode()
{
	UE_LOG(LogTemp, Warning, TEXT("abduction fail"));

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

