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

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Life")));

	OnHealt.Broadcast(life);
}

void APlayerBase::Damage(float amount)
{
	life -= amount;

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Life")));

	if (life <= 0)
	{
		DisableInput();
	}

	OnHealt.Broadcast(life);
}

void APlayerBase::AddItem()
{
	itemCounter++;
	OnAddItem.Broadcast(itemCounter);
}

void APlayerBase::DisableInput()
{
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (pawn)
		pawn->DisableInput(GetWorld()->GetFirstPlayerController());
}
