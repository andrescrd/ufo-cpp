#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Orbitiers.h"

const float multiply = 100;

AOrbitiers::AOrbitiers()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOrbitiers::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> staticMesh;
	GetComponents(staticMesh);
	currentStaticMesh = staticMesh[0];

	TSubclassOf<AOrbitiers> classToFind = AOrbitiers::StaticClass();
	TArray<AActor*> actorsTemp;

	UE_LOG(LogTemp, Warning, TEXT("start"));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorsTemp);

	UE_LOG(LogTemp, Warning, TEXT("ehre start"));

	if (actorsTemp.Num() > 0)
	{
		actors = actorsTemp;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dont find actors -*------*-"));
	}
}

// Called every frame
void AOrbitiers::Tick(float DeltaTime)
{
	if (actors.Num() > 0)
	{
		for (int i = 0; i < actors.Num(); i++)
		{
			if (actors[i] != this)
			{
				Attraction(actors[i]);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dont find actors"));
	}
}

void AOrbitiers::Attraction(AActor* objectToAttract)
{
	AOrbitiers* attractedActor = Cast<AOrbitiers>(objectToAttract);

	if (attractedActor)
	{
		TArray<UStaticMeshComponent*> staticMesh;
		attractedActor->GetComponents(staticMesh);	

		if (staticMesh.Num() > 0)
		{

			FVector difference = GetActorLocation() - attractedActor->GetActorLocation();
			float dist = difference.Size();
			float gravity = (6.7f * currentStaticMesh->GetMass() *staticMesh[0]->GetMass() * multiply) / (dist * dist);

			FVector gravityDirection = difference.GetSafeNormal();
			FVector force = gravity * gravityDirection;

			staticMesh[0]->AddForce(force, NAME_None, true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("dont have a static mesh"));
		}
	}
}

float AOrbitiers::GetMass()
{
	return mass;
}
