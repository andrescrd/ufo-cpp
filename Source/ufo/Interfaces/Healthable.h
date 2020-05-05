#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Healthable.generated.h"

UINTERFACE(MinimalAPI)
class UHealthable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UFO_API IHealthable
{
	GENERATED_BODY()

public:
	virtual void Health(float amount) = 0;
};
