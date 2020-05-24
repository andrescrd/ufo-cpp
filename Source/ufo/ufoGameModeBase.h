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

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	/** The widget instance that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;

public:
	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangePlayer(TSubclassOf<APawn> PlayerClass);

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
};
