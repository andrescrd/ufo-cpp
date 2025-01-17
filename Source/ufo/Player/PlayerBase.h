// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ufo/Interfaces/Healthable.h"
#include "ufo/Interfaces/Fighter.h"
#include "Delegates/DelegateCombinations.h"
#include "PlayerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDieDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDelegate, float, health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddItemDelegate, int, items);

UCLASS(Abstract)
class UFO_API APlayerBase : public APawn, public IHealthable, public IFighter
{
	GENERATED_BODY()

public:
	APlayerBase();

protected:

	void Health(float amount);
	void Damage(float amount);
	void AddItem();
	void UpdateDistance(float value);
	void DisableInput();
	void PlayerDie();

public:
	int initialLife = 0;
	bool isAlive = true;

	UPROPERTY(EditAnywhere) float life = 100;
	UPROPERTY(VisibleAnywhere) int itemCounter = 0;
	UPROPERTY(VisibleAnywhere) float distance = 0;

	FHealthDelegate OnHealt;
	FAddItemDelegate OnAddItem;
	FPlayerDieDelegate OnPlayerDie;
};
