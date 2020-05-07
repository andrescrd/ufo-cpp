#include "GetRAndomLocationTask.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"

EBTNodeResult::Type UGetRAndomLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());

	FNavLocation resultLocation;

	bool result = navSys->GetRandomPointInNavigableRadius(
		OwnerComp.GetOwner()->GetActorLocation(), radious, resultLocation);

	if (!result)
	{
		return EBTNodeResult::Type::Failed;
	}

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	blackboard->SetValueAsVector(locationKeySelector.SelectedKeyName, resultLocation.Location);
	return EBTNodeResult::Type::Succeeded;
}