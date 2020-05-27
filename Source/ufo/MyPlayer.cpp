#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "ufo/Interfaces/Healthable.h"
#include "ufo/Interfaces/Abducible.h"
#include "Player/PlayerBase.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMyPlayer::AMyPlayer() : APlayerBase()
{
	//PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	RootComponent = Body;
	Body->SetSimulatePhysics(true);
	Body->SetEnableGravity(false);
	Body->SetLinearDamping(1);
	Body->SetAngularDamping(1);
	Body->SetConstraintMode(EDOFMode::XYPlane);

	AbductionZone = CreateDefaultSubobject<UCapsuleComponent>("Abduction Zone Collider");
	AbductionZone->SetCapsuleSize(40, 100);
	AbductionZone->AttachTo(RootComponent);

	Abductor = CreateDefaultSubobject<USphereComponent>("Abductor Collider");
	Abductor->SetSphereRadius(40);
	Abductor->AttachTo(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 1.0f;

	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	Abductor->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnAbductorBeginOverlap);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("Vertical", this, &AMyPlayer::MoveVertical);
	playerInputComponent->BindAxis("Horizontal", this, &AMyPlayer::Rotate);

	playerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayer::StartFastBoost);

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
		OnStartFastBoost();
	}
}

void AMyPlayer::FastBoostTimer()
{
	hasFastBoost = true;
	FVector BoostVelocity =GetActorRotation().Vector().GetSafeNormal() * velocity * fastBoostForce * GetWorld()->GetDeltaSeconds();
	Body->AddImpulse(BoostVelocity, NAME_None, true);
}

void AMyPlayer::StopFastBoost()
{
	hasFastBoost = false;
	GetWorldTimerManager().ClearTimer(fastBoostTimerHandle);
	OnStopFastBoost();
}

void AMyPlayer::StartAbduction()
{
	abductionOn = true;
	GetWorldTimerManager().SetTimer(abductionTimerHandle, this, &AMyPlayer::AbductionTimer, 0.1, true);
	OnStartAbduction();
}

void AMyPlayer::AbductionTimer()
{
	if (abductionOn)
	{
		TArray<AActor*> overlappedActors;
		AbductionZone->GetOverlappingActors(overlappedActors);

		if (overlappedActors.Num() > 0)
		{
			IAbducible* abductible = nullptr;

			for (int i = 0; i < overlappedActors.Num(); i++)
			{
				abductible = Cast<IAbducible>(overlappedActors[i]);

				if (abductible)
					break;
			}

			if (abductible != nullptr)
				abductible->StartAbduction(FVector(0, 0, abductionForce * abductionMulitply));
		}
	}
}

void AMyPlayer::StopAbduction()
{
	abductionOn = false;
	GetWorldTimerManager().ClearTimer(abductionTimerHandle);
	OnStopAbduction();
}

void AMyPlayer::StartFire()
{
	Fire(10, 500);
	OnFire();
}

void AMyPlayer::Fire(int fireAmount, float fireRadio)
{
	for (int i = 0; i < fireAmount; i++)
	{
		FHitResult hitResult;

		FVector shootRadio = FVector(FMath::RandRange(-fireRadio, fireRadio), FMath::RandRange(-fireRadio, fireRadio), FMath::RandRange(-fireRadio, fireRadio));
		FVector dest = GetActorLocation() + GetActorRotation().Vector() * shootForce + shootRadio;

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
			IHealthable* other = Cast<IHealthable>(hitResult.GetActor());

			if (other)
				other->Damage(damage);
		}
	}
}

void AMyPlayer::OnAbductorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IAbducible* actorAbducible = Cast<IAbducible>(OtherActor);

	if (actorAbducible)
	{
		actorAbducible->SuccessAbduction();
		abductionCounter++;
		AddItem();
	}
}