// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "ufo/ufoGameModeBase.h"
#include "ufo/Player/PlayerBase.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "PlayerWidget.generated.h"

/**
 *
 */
UCLASS()
class UFO_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	//void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	AufoGameModeBase* gameMode;
	APlayerBase* player;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* lifeBar;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* itemCounterText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* timeText;

	UFUNCTION()
		void UpdateLife(float health);
	UFUNCTION()
		void UpdateItems(int item);
};
