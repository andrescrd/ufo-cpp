#include "MyProjectile.h"

AMyProjectile::AMyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AMyProjectile::Tick(float DeltaTime)
{

	FVector direction = movementDirection.GetSafeNormal() * speed * DeltaTime;
	AddActorLocalOffset(direction);
}

