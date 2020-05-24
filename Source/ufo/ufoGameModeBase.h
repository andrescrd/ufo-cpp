// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ufoGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class UFO_API AufoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AufoGameModeBase(const FObjectInitializer& ObjectInitializer);

protected:
	FTimerHandle timerHandle;
	int currentTime = 0;

	virtual void BeginPlay() override;

	UFUNCTION()
		void Timer();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY()
		UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere)
		int initialTime = 20;
	UPROPERTY(EditAnywhere)
		int difficulty = 1;

public:
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangePlayer(TSubclassOf<APawn> PlayerClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void StartGame();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void PauseGame();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void UpPauseGame();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void GoLevel1();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void GoLevel2();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void GoGameOver();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void RestartGame();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ExitGame();

	int GetTime();
};
