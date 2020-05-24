// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ufo/ufoGameModeBase.h"
#include "MainWidget.generated.h"

/**
 *
 */
UCLASS()
class UFO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	AufoGameModeBase* gameMode;

public:
	UFUNCTION(BlueprintCallable)
		void Play();
	UFUNCTION(BlueprintCallable)
		void Exit();
};
