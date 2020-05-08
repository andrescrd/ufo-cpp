#include "AIEnemyController.h"
#include "Perception/AIPerceptionComponent.h"

void AAIEnemyController::BeginPlay()
{
	aiPerception = GetAIPerceptionComponent();
	aiPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception Component");
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	aiPerception->ConfigureSense(*sightConfig);
}

void AAIEnemyController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* actor : UpdatedActors)
	{
	}
}