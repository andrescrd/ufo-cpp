#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/Damagable.h"


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

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("Vertical", this, &AMyPlayer::MoveVertical);
	playerInputComponent->BindAxis("Horizontal", this, &AMyPlayer::Rotate);

	playerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayer::StartFastBoost);
	// PlayerInputComponent->BindAction("Fast", IE_Released, this, &AMyPlayer::StopFastBoost);

	playerInputComponent->BindAction("Abduction", IE_Pressed, this, &AMyPlayer::StartAbduction);
	playerInputComponent->BindAction("Abduction", IE_Released, this, &AMyPlayer::StopAbduction);

	playerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPlayer::StartFire);
}

void AMyPlayer::MoveVertical(float value)
{
	FVector Movement = FVector(value * velocity * GetWorld()->GetDeltaSeconds(), 0, 0);
	AddActorLocalOffset(Movement, true);
}

void AMyPlayer::Rotate(float value)
{
	FRotator Rotation = FRotator(0, value * rotationVelocity * GetWorld()->GetDeltaSeconds(), 0);
	AddActorLocalRotation(Rotation);
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
	FVector BoostVelocity = GetActorRotation().Vector() * velocity * fastBoostForce * GetWorld()->GetDeltaSeconds();
	Body->SetPhysicsLinearVelocity(BoostVelocity, true);
}

void AMyPlayer::StopFastBoost()
{
	hasFastBoost = false;
	GetWorldTimerManager().ClearTimer(fastBoostTimerHandle);
}

void AMyPlayer::StartAbduction()
{
	abductionOn = true;
	// GetWorldTimerManager().SetTimer(abductionTimerHandle, this, &AMyPlayer::AbductionTimer, 0.5, true);
}

void AMyPlayer::AbductionTimer()
{
	// GetWorld()->byChanel
}

void AMyPlayer::StartFire()
{
	FHitResult hitResult;
	FVector dest = GetActorLocation() + GetActorRotation().Vector() * shootForce;

	GetWorld()->LineTraceSingleByChannel(
		hitResult,
		GetActorLocation(),
		dest,
		ECollisionChannel::ECC_Destructible);

	DrawDebugLine(GetWorld(),
		GetActorLocation(),
		dest,
		FColor::Red, false, 3);

	if (hitResult.GetActor())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Damaged: %s"), hitResult.GetActor()->GetName());
		IDamagable* damagable = Cast<IDamagable>(hitResult.GetActor());

		if (damagable)
		{
			damagable->Damage(damage);
		}
	}
}

void AMyPlayer::StopAbduction()
{
	abductionOn = false;
	// GetWorldTimerManager().ClearTimer(abductionTimerHandle);
}

void AMyPlayer::OnAbductionZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (abductionOn)
	{
		UE_LOG(LogTemp, Warning, TEXT("overlapped"));
	}
}

void AMyPlayer::OnAbductionZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("overlapped end"));
}