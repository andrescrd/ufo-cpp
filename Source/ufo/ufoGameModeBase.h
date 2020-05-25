// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include  "Player\PlayerBase.h"
#include "Engine/Engine.h"
#include "ufoGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class UFO_API AufoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		//public:
		//	AufoGameModeBase(const FObjectInitializer& ObjectInitializer);

private:
	class UUFOGameInstance* GameInstance;

protected:
	FTimerHandle timerHandle;
	FTimerHandle LevelSpawnTimer;
	int currentTime = 0;

	virtual void BeginPlay() override;

	UFUNCTION()
		void Timer();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> LevelCompleteWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> GameCompleteWidgetClass;


	UPROPERTY()
		UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere)
		int initialTime = 20;
	UPROPERTY(EditAnywhere)
		int difficulty = 1;

	int32 CurrentLevelIndex = 0;
	FString NextLevel;

	void CheckLevel();
	FString CleanLevelString(UObject* context);

public:
	void EndGame();
	void LevelComplete();
	void LoadNextGame();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void StartGame();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ExitGame();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	int GetTime();
};
