#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

UCLASS()
class UFO_API AMyProjectile : public AActor
{
	GENERATED_BODY()

public:
	AMyProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere) FVector movementDirection = FVector::ForwardVector;
	UPROPERTY(EditAnywhere) float speed = 100;
	UPROPERTY(EditAnywhere) float damage = 10;
};
