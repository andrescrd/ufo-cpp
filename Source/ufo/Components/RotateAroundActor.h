#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotateAroundActor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UFO_API URotateAroundActor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URotateAroundActor();

protected:
	float currentAngle = 0.f;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* rotateAroundActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rotationSpeed = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector rotationRadious = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector rotationAxis = FVector::UpVector;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
