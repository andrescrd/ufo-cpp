#include "PlayerBase.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework\Actor.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
//#include "Engine/Engine.h"

APlayerBase::APlayerBase()
{
	initialLife = life;
}

void APlayerBase::Health(float amount)
{
	life += amount;
	OnHealt.Broadcast(life);
}

void APlayerBase::Damage(float amount)
{
	life -= amount;

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Life")));

	if (life <= 0)
	{
		PlayerDie();
	}

	OnHealt.Broadcast(life);
}

void APlayerBase::AddItem()
{
	itemCounter++;
	OnAddItem.Broadcast(itemCounter);
}

void APlayerBase::UpdateDistance(float value)
{
	if (isAlive)
		distance += value;
}

void APlayerBase::DisableInput()
{
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (pawn)
		pawn->DisableInput(GetWorld()->GetFirstPlayerController());
}

void APlayerBase::PlayerDie()
{
	isAlive = false;
	DisableInput();
}
