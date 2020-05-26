// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "ufo/ufoGameModeBase.h"
#include "Engine/World.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AGameModeBase* gameModeBase = GetWorld()->GetAuthGameMode<AGameModeBase>();

	if (gameModeBase != nullptr)
		gameMode = Cast<AufoGameModeBase>(gameModeBase);

	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (pawn != nullptr)
	{
		player = Cast<APlayerBase>(pawn);
		player->OnHealt.AddDynamic(this, &UPlayerWidget::UpdateLife);
		player->OnAddItem.AddDynamic(this, &UPlayerWidget::UpdateItems);
	}
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (gameMode != nullptr && gameMode->UseTimeAsConditionEnd)
		UpdateTime(gameMode->GetTime());

	if (player != nullptr && gameMode != nullptr && !gameMode->UseTimeAsConditionEnd)
		UpdateDistance(player->distance);
}

void  UPlayerWidget::UpdateLife(float health)
{
	float lifePercent = health / player->initialLife;
	lifeBar->SetPercent(lifePercent);
}

void UPlayerWidget::UpdateDistance(float distance)
{
	//FText currentDistaceText = FText::FromString(FString::SanitizeFloat(distance));
	FNumberFormattingOptions options;
	options.MinimumFractionalDigits = 2;
	options.MaximumFractionalDigits = 2;
	FText currentDistaceText = FText::AsNumber(distance,&options);
	distanceText->SetText(currentDistaceText);
}

void  UPlayerWidget::UpdateItems(int items)
{
	FText itemText = FText::FromString(FString::FromInt(items));
	itemCounterText->SetText(itemText);
}

void UPlayerWidget::UpdateTime(int time)
{
	FText currentTimeText = FText::FromString(FString::FromInt(time));
	timeText->SetText(currentTimeText);
}

void UPlayerWidget::Quit()
{
	gameMode->ExitGame();
}

void UPlayerWidget::Pause()
{
	//gameMode->PauseGame();
}

void UPlayerWidget::Resume()
{
	//gameMode->UpPauseGame();
}
