#include "CheckDistanceService.h"
#include "BehaviorTree/BlackboardComponent.h"

void UCheckDistanceService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	UObject* objectTarget = blackboard->GetValueAsObject(playerKeySelector.SelectedKeyName);
	AActor* actorTarget = Cast<AActor>(objectTarget);

	if (actorTarget)
	{
		FVector controlledPawnLocation = OwnerComp.GetOwner()->GetActorLocation();
		FVector targetActorLocation = actorTarget->GetActorLocation();

		int distance = (controlledPawnLocation - targetActorLocation).Size();

		blackboard->SetValueAsBool(isInAttackRangeKeySelector.SelectedKeyName, (distance < minDistance));
	}
}