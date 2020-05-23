// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "ufo/ufoGameModeBase.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class UFO_API UPlayerWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	AufoGameModeBase* gameMode;
};
