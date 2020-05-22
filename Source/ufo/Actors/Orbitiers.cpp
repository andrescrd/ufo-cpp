#include "Orbitiers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

const float multiplier = 100;

AOrbitiers::AOrbitiers()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOrbitiers::BeginPlay()
{
	Super::BeginPlay();

	currentStaticMesh = GetStaticMesh();

	if (currentStaticMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("dont have a static mesh"));
		return;
	}

	TSubclassOf<AOrbitiers> classToFind = AOrbitiers::StaticClass();
	TArray<AActor*> actorsTemp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorsTemp);

	if (actorsTemp.Num() > 0)
	{
		actors = actorsTemp;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dont find actors"));
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
	IAttraction* attractedActor = Cast<IAttraction>(objectToAttract);

	if (attractedActor)
	{
		UStaticMeshComponent* attractedActorStaticMesh = attractedActor->GetStaticMesh();

		if (attractedActorStaticMesh == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("dont have a static mesh"));
			return;
		}

		FVector difference = GetActorLocation() - attractedActor->GetLocation();
		float dist = difference.Size();
		float gravity = (6.7f * GeAttractiontMass() * attractedActor->GeAttractiontMass() * multiplier) / (dist * dist);

		FVector gravityDirection = difference.GetSafeNormal();
		FVector force = gravity * gravityDirection;

		attractedActorStaticMesh->AddForce(force, NAME_None, true);
	}
}

float AOrbitiers::GeAttractiontMass()
{
	if (useDefaultMass)
	{
		return GetStaticMesh()->GetMass();
	}
	else {
		return mass;
	}
}

UStaticMeshComponent* AOrbitiers::GetStaticMesh()
{
	TArray< UStaticMeshComponent*> staticMeshArray;
	GetComponents(staticMeshArray);

	if (staticMeshArray.Num() > 0)
	{
		return staticMeshArray[0];
	}
	else
	{
		return nullptr;
	}
}

FVector AOrbitiers::GetLocation()
{
	return GetActorLocation();
}
