// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "ufoGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class UFO_API AufoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	//AufoGameModeBase(const FObjectInitializer& ObjectInitializer);

protected:
	class UUFOGameInstance* GameInstance;
	//class APlayerBase* PlayerBase;

	FTimerHandle TimerHandle;
	FTimerHandle LevelSpawnTimer;
	int CurrentTime = 0;
	int32 CurrentLevelIndex = 0;
	FString NextLevel;

	void BeginPlay() override;
	//void Tick(float deltaSecond) override;
	void CheckLevel();
	FString CleanLevelString(UObject* context);

	UFUNCTION()
		void Timer();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> LevelCompleteWidgetClass;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	//	TSubclassOf<UUserWidget> GameCompleteWidgetClass;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	//	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
public:
	void EndGame();
	void LevelComplete();
	void LoadNextGame();
	int GetTime();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void StartGame();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ExitGame();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		int InitialTime = 20;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		int Difficulty = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		float DistanceToReach = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		bool UseTimeAsConditionEnd = false;
};
