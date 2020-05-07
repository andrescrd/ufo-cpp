// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GetRAndomLocationTask.generated.h"

/**
 *
 */
UCLASS()
class UFO_API UGetRAndomLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere) float radious = 5000;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector locationKeySelector;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
