#include "PlayerBase.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

APlayerBase::APlayerBase()
{
	initialLife = life;
}

void APlayerBase::Health(float amount)
{
	life += amount;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Life")));
}

void APlayerBase::Damage(float amount)
{
	life -= amount;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Life")));

	if (life <= 0)
	{
		InputComponent->Deactivate();
	}
}

void APlayerBase::AddItem()
{
	itemCounter++;
}
