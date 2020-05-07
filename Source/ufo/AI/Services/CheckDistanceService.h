// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CheckDistanceService.generated.h"

/**
 *
 */
UCLASS()
class UFO_API UCheckDistanceService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) float minDistance;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector playerKeySelector;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector isInAttackRangeKeySelector;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
