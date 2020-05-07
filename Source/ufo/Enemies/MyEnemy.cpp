#include "MyEnemy.h"

AMyEnemy::AMyEnemy()
{
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
}

//void AMyEnemy::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyEnemy::Damage(float amount)
{
	life -= amount;

	if (life <= 0)
	{
		Destroy();
	}
}

void AMyEnemy::Health(float amount)
{
	life += amount;

	if (life >= maxLife)
	{
		life = maxLife;
	}
}

void AMyEnemy::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("I am shooting"));
}

