// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UGravityComponent::UGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

FVector UGravityComponent::RotateActorAroundPoint(AActor* other, FVector targetLocation, float currentRadious, float angle, float rotationRate)
{
		FVector location = other->GetActorLocation();
		FVector rotatorVector = FVector(currentRadious, 0, 0).RotateAngleAxis(rotationRate + angle, FVector(0, 0, 1));
	
		FVector rotatorResult = location + rotatorVector;
		GetOwner()->GetParentActor()->SetActorLocation(rotatorResult);
	
		return location;
}

// Called when the game starts
void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	initialLocation = GetOwner()->GetParentActor()->GetActorLocation();
}

// Called every frame
void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	currentRotation += rotationSpeed * DeltaTime;

	if (targetActor)
	{
		RotateActorAroundPoint(targetActor, initialLocation, radious, startingAngle, currentRotation);
	}
}
