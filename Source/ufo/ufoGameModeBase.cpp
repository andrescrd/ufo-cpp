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
//
//AufoGameModeBase::AufoGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
//{
//	PrimaryActorTick.bCanEverTick = true;
//}
//
void AufoGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UUFOGameInstance* gameInstance = GetGameInstance<UUFOGameInstance>();
	if (gameInstance != nullptr) {
		GameInstance = gameInstance;
		ChangeWidget(StartingWidgetClass);
		CheckLevel();
	}
	else
	{
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
		NextLevel = GameInstance->GameOverLevel;
	}

	UE_LOG(LogTemp, Warning, TEXT("Next Levelt %s"), *NextLevel);
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
	UE_LOG(LogTemp, Warning, TEXT("PlayerDie"));

	FName LavelToLoad = FName(*GameInstance->GameOverLevel);
	UGameplayStatics::OpenLevel(this, LavelToLoad, true);
}

void AufoGameModeBase::LevelComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("Level Complete"));

	if (LevelCompleteWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Complete change widget"));

		ChangeWidget(LevelCompleteWidgetClass);

		UE_LOG(LogTemp, Warning, TEXT("Widget change"));

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
		EndGame();
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
	if (UseTimeAsConditionEnd)
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AufoGameModeBase::Timer, 1.0f, true);
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
	return CurrentTime;
}

void AufoGameModeBase::Timer()
{
	if (++CurrentTime >= InitialTime)
	{
		LevelComplete();
		GetWorldTimerManager().ClearTimer(TimerHandle);;
	}
}
