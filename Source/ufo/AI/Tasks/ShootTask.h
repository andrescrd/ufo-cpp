// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShootTask.generated.h"

/**
 *
 */
UCLASS()
class UFO_API UShootTask : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere) FBlackboardKeySelector playerKeySelector;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
