#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ufo\Interfaces\Abducible.h"
#include "MyEnemyObjective.generated.h"

UCLASS()
class UFO_API AMyEnemyObjective : public ACharacter, public IAbducible
{
	GENERATED_BODY()

public:
	AMyEnemyObjective();

protected:
	//virtual void BeginPlay() override;

public:
	//virtual void Tick(float DeltaTime) override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartAbducted();
	void AbductedFail();
};
