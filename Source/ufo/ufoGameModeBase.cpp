// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ufoGameModeBase.h"
#include "Engine/World.h"
#include "UI/PlayerWidget.h"
#include "UI/MainWidget.h"
#include "Player/PlayerBase.h"
#include "Kismet/KismetSystemLibrary.h"

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
	{
		DefaultPawnClass = PlayerClass;
	}
}

void AufoGameModeBase::GoLevel1()
{
	GetWorld()->ServerTravel("level1");
}

void AufoGameModeBase::GoLevel2()
{
	GetWorld()->ServerTravel("level2");
}

void AufoGameModeBase::GoGameOver()
{
	GetWorld()->ServerTravel("gameover");
}

void AufoGameModeBase::RestartGame()
{
	GoLevel1();
	ResetLevel();
}

void AufoGameModeBase::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
