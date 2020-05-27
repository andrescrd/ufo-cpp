#include "MyProjectile.h"
#include "ufo/Components/DirectionalGravity.h"

AMyProjectile::AMyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	DirectionalGravity = CreateDefaultSubobject<UDirectionalGravity>(TEXT("Directional Gravity"));
	DirectionalGravity->gravity = 0.0f;
	AddOwnedComponent(DirectionalGravity);

	Multiplier = 50.f;
}

void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AMyProjectile::Tick(float DeltaTime)
{
	AddActorLocalOffset(Direction * Multiplier);
}

