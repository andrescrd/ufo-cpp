// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UFOGameInstance.generated.h"

/**
 *
 */
UCLASS()
class UFO_API UUFOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
		TArray<FString> Levels;
};
