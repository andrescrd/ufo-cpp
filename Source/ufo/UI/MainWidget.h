// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UFO_API UMainWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		void Play();
	UFUNCTION(BlueprintCallable)
		void Exit();
};
