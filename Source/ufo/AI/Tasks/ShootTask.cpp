#include "ShootTask.h"
#include "AIController.h"
#include "ufo/Interfaces//EnemyAttack.h"

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

	targetOwner->Attack();

	return EBTNodeResult::Type::Succeeded;
}