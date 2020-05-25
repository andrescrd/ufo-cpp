// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	AufoGameModeBase* gameMode;
	APlayerBase* player;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* lifeBar;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* itemCounterText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* timeText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* distanceText;

	UFUNCTION()
		void UpdateLife(float health);
	UFUNCTION()
		void UpdateDistance(float distance);
	UFUNCTION()
		void UpdateItems(int item);
	UFUNCTION()
		void UpdateTime(int time);	

	UFUNCTION(BlueprintCallable)
		void Pause();
	UFUNCTION(BlueprintCallable)
		void Resume();
	UFUNCTION(BlueprintCallable)
		void Quit();
};
