#include "MyEnemy.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "ufo/Interfaces/Damagable.h"

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

void AMyEnemy::Attack(AActor* actor)
{
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByChannel(
		hitResult,
		GetActorLocation(),
		actor->GetActorLocation(),
		ECollisionChannel::ECC_Destructible
	);

	DrawDebugLine(GetWorld(),
		GetActorLocation(),
		actor->GetActorLocation(),		
		FColor::Blue, false, 3);

	if (hitResult.GetActor())
	{
		IDamagable* damagable = Cast<IDamagable>(hitResult.GetActor());

		if (damagable)
		{
			damagable->Damage(damage);
		}
	}
}

