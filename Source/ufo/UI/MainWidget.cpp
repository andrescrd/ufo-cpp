// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Engine/World.h"
#include "ufo/ufoGameModeBase.h"

void UMainWidget::NativeConstruct()
{
	AGameModeBase* gameModeBase = GetWorld()->GetAuthGameMode<AGameModeBase>();

	if (gameModeBase != nullptr)
		gameMode = Cast<AufoGameModeBase>(gameModeBase);
}

void UMainWidget::Play()
{
	gameMode->GoLevel1();
}

void UMainWidget::Exit()
{
	gameMode->ExitGame();
}
