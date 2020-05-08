#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIEnemyController.generated.h"
/**
 * 
 */
UCLASS()
class UFO_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UAISenseConfig_Sight* sightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)	UAIPerceptionComponent* aiPerception;

	//UPROPERTY(EditAnywhere)	AActor* actorToAttack;
	//UPROPERTY(EditAnywhere) FName playerKeySelector;


	UFUNCTION()
	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
};
