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

	if (rotateAroundActor != nullptr)
	{
		if (rotationRadious == 0)
		{
			rotationRadious = (GetOwner()->GetActorLocation() - rotateAroundActor->GetActorLocation()).Size();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Rotator Around Actor is not set on %s"), *GetReadableName());
	}
}

void URotateAroundActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActive() && rotateAroundActor != nullptr)
	{
		currentAngle += rotationSpeed * DeltaTime;

		if (currentAngle > 360.f)
			currentAngle = 0;

		FVector newLocation = rotateAroundActor->GetActorLocation() + FVector(rotationRadious, rotationRadious, rotationRadious).RotateAngleAxis(currentAngle, rotationAxis);

		//GetOwner()->SetActorLocationAndRotation(newLocation, FRotator(0, currentAngle, 0));
		GetOwner()->SetActorLocation(newLocation);
	}
}

