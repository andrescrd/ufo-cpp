// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UFO_API UGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGravityComponent();

private:
	FVector RotateActorAroundPoint(AActor* other, FVector targetLocation, float currentRadious, float angle, float rotationRate);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	FVector initialLocation;
	float currentRotation;
	float startingAngle;
	float rotationSpeed = 50;

	UPROPERTY(EditAnywhere) float radious = 200;
	UPROPERTY(EditAnywhere) AActor* targetActor;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
