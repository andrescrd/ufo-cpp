#include "GameFramework\Actor.h"
#include "RotateAroundActor.h"

URotateAroundActor::URotateAroundActor()
{	
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = false;
}

void URotateAroundActor::BeginPlay()
{
	Super::BeginPlay();

	if (rotateAroundActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Rotator Around Actor is not set on %s"), *GetReadableName());
		return;
	}

	if (rotationRadious.IsZero())
	{
		rotationRadious = GetOwner()->GetActorLocation() - rotateAroundActor->GetActorLocation();
	}	
}

void URotateAroundActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActive() && rotateAroundActor != nullptr)
	{
		currentAngle += rotationSpeed * DeltaTime;

		if (currentAngle > 360.f)
			currentAngle -= 360.f;

		FVector newLocation = rotateAroundActor->GetActorLocation() + rotationRadious.RotateAngleAxis(currentAngle, rotationAxis);

		GetOwner()->SetActorLocationAndRotation(newLocation, FRotator(0, currentAngle, 0));
	}
}

