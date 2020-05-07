#include "MyEnemyObjective.h"
#include "GameFramework/CharacterMovementComponent.h"


AMyEnemyObjective::AMyEnemyObjective()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyEnemyObjective::BeginPlay()
{
	Super::BeginPlay();
}


void AMyEnemyObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyEnemyObjective::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AMyEnemyObjective::StartAbduction(FVector abductionForce)
{
	UE_LOG(LogTemp, Warning, TEXT("overlapped"))
		GetCharacterMovement()->AddForce(abductionForce);
}

void AMyEnemyObjective::SuccessAbduction()
{
	Destroy();
}
