// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ufoGameModeBase.h"
#include "Engine/World.h"
#include "UI/PlayerWidget.h"
#include "UI/MainWidget.h"
#include "Player/PlayerBase.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include  "GameInstance/UFOGameInstance.h"

void AufoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	

	UUFOGameInstance* gameInstance = GetGameInstance<UUFOGameInstance>();
	if (gameInstance != nullptr) {
		GameInstance = gameInstance;
		ChangeWidget(StartingWidgetClass);
		CheckLevel();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Fail to load GameInstance"));
	}
}

void AufoGameModeBase::CheckLevel()
{
	FString CurrentLevelName = CleanLevelString(GetWorld());
	GameInstance->Levels.Find(CurrentLevelName, CurrentLevelIndex);

	if (CurrentLevelIndex < GameInstance->Levels.Num() - 1)
	{
		NextLevel = GameInstance->Levels[CurrentLevelIndex + 1];
	}
	else
	{
		NextLevel = "End";
	}
}

FString AufoGameModeBase::CleanLevelString(UObject* context)
{
	if (GEngine)
	{
		FString Prefix = GEngine->GetWorldFromContextObject(context)->StreamingLevelsPrefix;
		FString LevelName = GetWorld()->GetMapName();

		return LevelName.RightChop(Prefix.Len());
	}
	else
	{
		return "No map found";
	}
}

void AufoGameModeBase::EndGame()
{
	FString LevelString = GetWorld()->GetMapName();
	FName LavelToLoad = FName(*LevelString);

	UGameplayStatics::OpenLevel(this, LavelToLoad, true);
}

void AufoGameModeBase::LevelComplete()
{
	if (LevelCompleteWidgetClass)
	{
		ChangeWidget(LevelCompleteWidgetClass);
		GetWorldTimerManager().SetTimer(LevelSpawnTimer, this, &AufoGameModeBase::LoadNextGame, 4.0f, false);
	}
}

void AufoGameModeBase::LoadNextGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Level %s"), *NextLevel);

	if (GameInstance->Levels.Contains(NextLevel))
	{
		FName LevelToLoad = FName(*NextLevel);
		UGameplayStatics::OpenLevel(this, LevelToLoad, true);
	}
	else
	{
		if (CurrentWidget->GetClass() == LevelCompleteWidgetClass)
		{

		}
	}
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

void AufoGameModeBase::StartGame()
{
	GetWorldTimerManager().SetTimer(timerHandle, this, &AufoGameModeBase::Timer, 1.0f, true);
}
//
//void AufoGameModeBase::PauseGame()
//{
//	UGameplayStatics::SetGamePaused(GetWorld(), true);
//}
//
//void AufoGameModeBase::UpPauseGame()
//{
//	UGameplayStatics::SetGamePaused(GetWorld(), false);
//}
//
//void AufoGameModeBase::GoLevel1()
//{
//	UGameplayStatics::OpenLevel(GetWorld(), "level1");
//}
//
//void AufoGameModeBase::GoLevel2()
//{
//	UGameplayStatics::OpenLevel(GetWorld(), "level2");
//}
//
//void AufoGameModeBase::GoGameOver()
//{
//	UGameplayStatics::OpenLevel(GetWorld(), "gameover");
//}
//
//void AufoGameModeBase::RestartGame()
//{
//	GoLevel1();
//}

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
		LevelComplete();
		GetWorldTimerManager().ClearTimer(timerHandle);;
	}
}
