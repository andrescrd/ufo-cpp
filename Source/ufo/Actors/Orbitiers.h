#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "ufo/Interfaces/Attraction.h"
#include "Orbitiers.generated.h"

UCLASS()
class UFO_API AOrbitiers : public AActor, public IAttraction
{
	GENERATED_BODY()

public:
	AOrbitiers();

private:
	TArray<AActor*> actors;
	UStaticMeshComponent* currentStaticMesh;

protected:
	 void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere) float mass;
	UPROPERTY(EditAnywhere) bool useDefaultMass = false;

	// Called every frame
	void Tick(float DeltaTime) override;

	void Attraction(AActor* objectToAttract);
	float GeAttractiontMass();
	UStaticMeshComponent* GetStaticMesh();
	FVector GetLocation();
};
