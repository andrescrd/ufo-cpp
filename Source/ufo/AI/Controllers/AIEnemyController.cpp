#include "AIEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ufo/Interfaces/Fighter.h"
#include "ufo/Interfaces/EnemyAttack.h"

AAIEnemyController::AAIEnemyController()
{
	aiPerception = GetAIPerceptionComponent();
	aiPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception Component");
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	aiPerception->ConfigureSense(*sightConfig);

	aiPerception->OnPerceptionUpdated.AddDynamic(this, &AAIEnemyController::ActorsPerceptionUpdated);
}

void AAIEnemyController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	
	UBlackboardData* currentBB = behaviorComp->BlackboardAsset;
	UseBlackboard(currentBB, Blackboard);
	RunBehaviorTree(behaviorComp);

	IEnemyAttack* enemy = Cast<IEnemyAttack>(pawn->GetOwner());

	if (!enemy)
	{
		Blackboard->SetValueAsBool(isAgresiveKeySelector, true);
	}
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