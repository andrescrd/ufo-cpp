// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Attraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UFO_API IAttraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Attraction(AActor* other) = 0;
	virtual float GetMass() = 0;
};
