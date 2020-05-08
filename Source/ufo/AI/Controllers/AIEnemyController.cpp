#include "AIEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ufo/Interfaces/Fighter.h"

AAIEnemyController::AAIEnemyController()
{
	aiPerception = GetAIPerceptionComponent();
	aiPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception Component");
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	sightConfig->DetectionByAffiliation.bDetectEnemies = true;

	aiPerception->ConfigureSense(*sightConfig);
}

void AAIEnemyController::OnPossess(APawn* pawn)
{
	UBlackboardData* currentBB = behaviorComp->BlackboardAsset;
	UseBlackboard(currentBB, Blackboard);
	RunBehaviorTree(behaviorComp);
}

void AAIEnemyController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* actor : UpdatedActors)
	{
		IFighter* actorFighter = Cast<IFighter>(actor);

		if (actorFighter)
		{
			FActorPerceptionBlueprintInfo info;
			aiPerception->GetActorsPerception(actor, info);

			if (info.LastSensedStimuli[0].WasSuccessfullySensed())
			{
				Blackboard->SetValueAsObject(playerKeySelector, actor);
			}
			else
			{
				Blackboard->ClearValue(playerKeySelector);
			}
		}
	}
}