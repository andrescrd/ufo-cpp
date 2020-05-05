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
	void StartAbduction();
	void AbductedFail();
};
