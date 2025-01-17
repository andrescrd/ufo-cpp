#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Abducible.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbducible : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UFO_API IAbducible
{
	GENERATED_BODY()

public:
	virtual void StartAbduction(FVector abductionForce) = 0;
	virtual void SuccessAbduction() = 0;
	//virtual void DisableAbductionMode() = 0;
};
