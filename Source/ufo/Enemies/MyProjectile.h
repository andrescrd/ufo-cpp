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
private: 
	FVector initialLocation;

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// declare our float variables
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = Movement)
		FVector PointOfRotation;
	
	UPROPERTY(EditAnywhere, Category = Movement)
		float AngleAxis;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector Dimensions;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector AxisVector;

	UPROPERTY(EditAnywhere, Category = Movement)
		float Multiplier;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector Direction = FVector::ForwardVector;
};
