#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damagable.generated.h"

UINTERFACE(MinimalAPI)
class UDamagable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UFO_API IDamagable
{
	GENERATED_BODY()

public:
	virtual void Damage(float amount);
};
