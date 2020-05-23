// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Engine/World.h"
#include "ufo/ufoGameModeBase.h"
#include "GenericPlatform/GenericPlatformMisc.h"

void UMainWidget::Play()
{
	GetWorld()->ServerTravel("level1");
}

void UMainWidget::Exit()
{
	FGenericPlatformMisc::RequestExit(false);
}
