#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"

AMyPlayer::AMyPlayer()
{
	// PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	body->SetupAttachment(GetRootComponent());
	body->SetSimulatePhysics(true);
	body->SetEnableGravity(false);
	body->SetLinearDamping(1);
	body->SetAngularDamping(1);
	body->SetConstraintMode(EDOFMode::XYPlane);

	abductionZone = CreateDefaultSubobject<UCapsuleComponent>("Abduction Zone Collider");
	abductionZone->SetCapsuleSize(40, 100);
	abductionZone->Deactivate();
	abductionZone->SetupAttachment(body);
	// camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	// camera->SetupAttachment(body);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	abductionZone->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnAbductionZoneBeginOverlap);
	abductionZone->OnComponentEndOverlap.AddDynamic(this, &AMyPlayer::OnAbductionZoneEndOverlap);
}

// void AMyPlayer::Tick(float DeltaTime)
// {

// }

void AMyPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Vertical", this, &AMyPlayer::MoveVertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyPlayer::Rotate);

	PlayerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayer::StartFastBoost);
	// PlayerInputComponent->BindAction("Fast", IE_Released, this, &AMyPlayer::StopFastBoost);

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
	if (!hasFastBoost)
	{
		GetWorldTimerManager().SetTimer(fastBoostTimerHandle, this, &AMyPlayer::FastBoostTimer, 0.3, true);
		GetWorldTimerManager().SetTimer(stopFastBoostTimerHandle, this, &AMyPlayer::StopFastBoost, fastBoostDuration, false);
	}
}

void AMyPlayer::FastBoostTimer()
{
	hasFastBoost = true;
	FVector boostVelocity = GetActorRotation().Vector() * velocity * fastBoostForce * GetWorld()->GetDeltaSeconds();
	body->SetPhysicsLinearVelocity(boostVelocity, true);
}

void AMyPlayer::StopFastBoost()
{
	hasFastBoost = false;
	GetWorldTimerManager().ClearTimer(fastBoostTimerHandle);
}

void AMyPlayer::StartAbduction()
{
	abductionOn = true;
	abductionZone->Activate();
	// GetWorldTimerManager().SetTimer(abductionTimerHandle, this, &AMyPlayer::AbductionTimer, 0.5, true);
}

void AMyPlayer::AbductionTimer()
{
	// GetWorld()->byChanel
}

void AMyPlayer::StopAbduction()
{
	abductionOn = false;
	abductionZone->Deactivate();
	// GetWorldTimerManager().ClearTimer(abductionTimerHandle);
}

void AMyPlayer::OnAbductionZoneEndOverlap(AActor *me, AActor *other)
{
	UE_LOG(LogTemp, Warning, FText("overlapped"));
}

void AMyPlayer::OnAbductionZoneEndOverlap(AActor *me, AActor *other)
{
	UE_LOG(LogTemp, Warning, FText("overlapped end"));
}