#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyController.generated.h"
/**
 *
 */
UCLASS()
class UFO_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AAIEnemyController();

private:
	class UAIPerceptionComponent* aiPerception;
	class UAISenseConfig_Sight* sightConfig;

	//UPROPERTY(EditAnywhere) class UB* blackboardComp;
	UPROPERTY(EditAnywhere) class UBehaviorTree* behaviorComp;
	//UPROPERTY(EditAnywhere)	TSubclassOf<class AActor*> actorToAttack;
	UPROPERTY(EditAnywhere) FName playerKeySelector;

public:
	virtual void OnPossess(APawn* InPawn) override;

	//UFUNCTION()
	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;
};
