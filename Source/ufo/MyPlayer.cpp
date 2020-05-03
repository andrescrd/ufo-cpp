#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	body->SetupAttachment(GetRootComponent());

	// camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	// camera->SetupAttachment(body);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayer::Tick(float DeltaTime)
{
	if (canUseFastBoost)
	{
		FVector movement = FVector(fastBoostVelocity * DeltaTime, 0, 0);
		AddActorLocalOffset(movement, true);
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Vertical", this, &AMyPlayer::MoveVertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyPlayer::Rotate);

	PlayerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayer::StartFastBoost);
	PlayerInputComponent->BindAction("Fast", IE_Released, this, &AMyPlayer::StopFastBoost);

	PlayerInputComponent->BindAction("Abduction", IE_Pressed, this, &AMyPlayer::StartAbduction);
	PlayerInputComponent->BindAction("Abduction", IE_Released, this, &AMyPlayer::StopAbduction);
}

void AMyPlayer::MoveVertical(float value)
{
	FVector movement = FVector(value * velocity * GetWorld()->GetDeltaSeconds(), 0, 0);
	AddActorLocalOffset(movement, true);
}

void AMyPlayer::Rotate(float value)
{
	FRotator rotation = FRotator(0, value * rotationVelocity * GetWorld()->GetDeltaSeconds(), 0);
	AddActorLocalRotation(rotation);
}

void AMyPlayer::StartFastBoost()
{
		canUseFastBoost = true;
}

void AMyPlayer::StopFastBoost()
{
	canUseFastBoost = false;
}

void AMyPlayer::AbductionTimer()
{
}

void AMyPlayer::StartAbduction()
{
}

void AMyPlayer::StopAbduction()
{
}