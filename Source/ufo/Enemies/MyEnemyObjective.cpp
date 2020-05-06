#include "MyEnemyObjective.h"
#include "GameFramework/CharacterMovementComponent.h"


AMyEnemyObjective::AMyEnemyObjective()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void AMyEnemyObjective::StartAbduction(FVector abductionForce)
{
	GetCharacterMovement()->AddForce(abductionForce);
}