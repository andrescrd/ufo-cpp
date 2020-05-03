#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(GetRootComponent());

	body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	body->SetupAttachment(camera);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// void AMyPlayer::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }

void AMyPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Vertical", this, &AMyPlayer::MoveVertical);
	PlayerInputComponent->BindAxis("Rotate", this, &AMyPlayer::Rotate);

	PlayerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayer::FastBoost);

	PlayerInputComponent->BindAction("Abduction", IE_Pressed, this, &AMyPlayer::StartAbduction);
	PlayerInputComponent->BindAction("Abduction", IE_Released, this, &AMyPlayer::StopAbduction);
}

void AMyPlayer::MoveVertical(float value)
{
	AddActorLocalOffset(value * velocity * GetWorld()->GetDeltaSeconds(), true);
}

void AMyPlayer::Rotate(float value)
{
	AddActorLocalRotation(value * rotationVelocity * GetWorld()->GetDeltaSeconds());
}

void AMyPlayer::FastBoost()
{
	body->SetPhysicsLinearVelocity(GetActorForwardVector() * fastBoostForce, true);
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