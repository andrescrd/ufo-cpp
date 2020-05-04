#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"

AMyPlayer::AMyPlayer()
{
	// PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(GetRootComponent());
	Body->SetSimulatePhysics(true);
	Body->SetEnableGravity(false);
	Body->SetLinearDamping(1);
	Body->SetAngularDamping(1);
	Body->SetConstraintMode(EDOFMode::XYPlane);

	AbductionZone = CreateDefaultSubobject<UCapsuleComponent>("Abduction Zone Collider");
	AbductionZone->SetCapsuleSize(40, 100);
	AbductionZone->Deactivate();
	AbductionZone->SetupAttachment(Body);
	// camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	// camera->SetupAttachment(body);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	AbductionZone->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnAbductionZoneBeginOverlap);
	AbductionZone->OnComponentEndOverlap.AddDynamic(this, &AMyPlayer::OnAbductionZoneEndOverlap);
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

void AMyPlayer::MoveVertical(float Value)
{
	FVector Movement = FVector(Value * Velocity * GetWorld()->GetDeltaSeconds(), 0, 0);
	AddActorLocalOffset(Movement, true);
}

void AMyPlayer::Rotate(float Value)
{
	FRotator Rotation = FRotator(0, Value * RotationVelocity * GetWorld()->GetDeltaSeconds(), 0);
	AddActorLocalRotation(Rotation);
}

void AMyPlayer::StartFastBoost()
{
	if (!HasFastBoost)
	{
		GetWorldTimerManager().SetTimer(FastBoostTimerHandle, this, &AMyPlayer::FastBoostTimer, 0.3, true);
		GetWorldTimerManager().SetTimer(StopFastBoostTimerHandle, this, &AMyPlayer::StopFastBoost, FastBoostDuration, false);
	}
}

void AMyPlayer::FastBoostTimer()
{
	HasFastBoost = true;
	FVector BoostVelocity = GetActorRotation().Vector() * Velocity * FastBoostForce * GetWorld()->GetDeltaSeconds();
	Body->SetPhysicsLinearVelocity(BoostVelocity, true);
}

void AMyPlayer::StopFastBoost()
{
	HasFastBoost = false;
	GetWorldTimerManager().ClearTimer(FastBoostTimerHandle);
}

void AMyPlayer::StartAbduction()
{
	AbductionOn = true;
	AbductionZone->Activate();
	// GetWorldTimerManager().SetTimer(abductionTimerHandle, this, &AMyPlayer::AbductionTimer, 0.5, true);
}

void AMyPlayer::AbductionTimer()
{
	// GetWorld()->byChanel
}

void AMyPlayer::StopAbduction()
{
	AbductionOn = false;
	AbductionZone->Deactivate();
	// GetWorldTimerManager().ClearTimer(abductionTimerHandle);
}

void AMyPlayer::OnAbductionZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  
{
	UE_LOG(LogTemp, Warning, TEXT("overlapped"));
}

void AMyPlayer::OnAbductionZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	UE_LOG(LogTemp, Warning, TEXT("overlapped end"));
}