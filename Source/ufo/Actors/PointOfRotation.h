// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointOfRotation.generated.h"

UCLASS()
class UFO_API APointOfRotation : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APointOfRotation();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereCollision;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
