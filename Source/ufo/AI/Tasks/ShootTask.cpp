#include "ShootTask.h"
#include "AIController.h"
#include "ufo/Interfaces//EnemyAttack.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UShootTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* targetController = Cast<AAIController>(OwnerComp.GetOwner());
	
	if (!targetController) 
	{
		return EBTNodeResult::Type::Failed;
	}

	IEnemyAttack* targetOwner = Cast<IEnemyAttack>(targetController->GetPawn());

	if (!targetOwner)
	{
		return EBTNodeResult::Type::Failed;
	}

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	UObject* object =  blackboard->GetValueAsObject(playerKeySelector.SelectedKeyName);

	if (!object)
	{
		return EBTNodeResult::Type::Failed;
	}

	AActor* actor = Cast<AActor>(object);
	targetOwner->Attack(actor);

	return EBTNodeResult::Type::Succeeded;
}