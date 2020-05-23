// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ufo/Interfaces/Healthable.h"
#include "ufo/Interfaces/Fighter.h"
#include "PlayerBase.generated.h"

UCLASS(Abstract)
class UFO_API APlayerBase : public APawn, public IHealthable, public IFighter
{
	GENERATED_BODY()

public:
	 APlayerBase();

protected:
	int initialLife = 0;

	void Health(float amount);
	void Damage(float amount);
	void AddItem();

public:
	UPROPERTY(EditAnywhere)
		int life = 100;
	UPROPERTY(EditAnywhere)
		int itemCounter = 0;
};
