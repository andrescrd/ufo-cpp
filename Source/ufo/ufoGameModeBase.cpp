// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ufoGameModeBase.h"
#include "Engine/World.h"
#include "UI/PlayerWidget.h"
#include "UI/MainWidget.h"
#include "Player/PlayerBase.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


AufoGameModeBase::AufoGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AufoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeWidget(StartingWidgetClass);
	//ChangePlayer(StartingPawnClass);
}

void AufoGameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr)
			CurrentWidget->AddToViewport();
	}
}

void AufoGameModeBase::ChangePlayer(TSubclassOf<APawn> PlayerClass)
{
	if (PlayerClass != nullptr)
		DefaultPawnClass = PlayerClass;
}

void AufoGameModeBase::StartGame()
{
	GetWorldTimerManager().SetTimer(timerHandle, this, &AufoGameModeBase::Timer, 1.0f, true);
}

void AufoGameModeBase::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AufoGameModeBase::UpPauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void AufoGameModeBase::GoLevel1()
{
	UGameplayStatics::OpenLevel(GetWorld(), "level1");
}

void AufoGameModeBase::GoLevel2()
{
	UGameplayStatics::OpenLevel(GetWorld(), "level2");
}

void AufoGameModeBase::GoGameOver()
{
	UGameplayStatics::OpenLevel(GetWorld(), "gameover");
}

void AufoGameModeBase::RestartGame()
{
	GoLevel1();
}

void AufoGameModeBase::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

int AufoGameModeBase::GetTime()
{
	return currentTime;
}

void AufoGameModeBase::Timer()
{
	if (++currentTime >= initialTime)
	{
		GoLevel2();
		GetWorldTimerManager().ClearTimer(timerHandle);;
	}
}
